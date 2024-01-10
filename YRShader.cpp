#include "YRShader.h"

YRShader::YRShader(std::string& vertexShaderFilePath, std::string& fragmentShaderFilePath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexShaderFilePath);
        fShaderFile.open(fragmentShaderFilePath);

        std::string vshaderStr((std::istreambuf_iterator<char>(vShaderFile)),
            std::istreambuf_iterator<char>());
        std::string fshaderStr((std::istreambuf_iterator<char>(fShaderFile)),
            std::istreambuf_iterator<char>());
        //std::stringstream vShaderStream, fShaderStream;
        //vShaderStream << vShaderFile.rdbuf();
        //fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();

        //vertexCode = vShaderStream.str();
        //fragmentCode = fShaderStream.str();

        vertexCode = vshaderStr;
        fragmentCode = fshaderStr;
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    unsigned int vertex, fragment;
    vertex = this->createVertexShader(vertexShaderSource);
    fragment = this->createFragmentShader(fragmentShaderSource);
    this->id = this->creatLinkShadersProgram(vertex, fragment);
}

void YRShader::use()
{
    glUseProgram(this->id);
}

void YRShader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void YRShader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void YRShader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void YRShader::setMat4(const std::string& name, glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void YRShader::setVec3(const std::string& name, glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

unsigned int YRShader::createVertexShader(const char* vertexShaderSource)
{
    // vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return vertexShader;
}

unsigned int YRShader::createFragmentShader(const char* fragmentShaderSource)
{
    // fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return fragmentShader;
}

unsigned int YRShader::creatLinkShadersProgram(unsigned int& vertexShader, unsigned int& fragmentShader)
{
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
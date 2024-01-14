#include <iostream>

#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "YRShader.h"
#include "YRTexture.h"
#include "YRWindow.h"
//#include "YRCamera.h"

#include "YRCameraData.h"
#include "YRPosData.h"

float colorAdjust = 0.5;
float leftRightAdjust = 0.0;
float upDownAdjust = 0.0;

glm::vec3 cameraPos = YRCameraData::cameraPos;
glm::vec3 cameraFront = YRCameraData::cameraFront;
glm::vec3 cameraUp = YRCameraData::cameraUp;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

// camera
YRCamera myCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

// lighting
glm::vec3 lightPos(0.0f, 1.0f, 1.0f);
auto lightPosVec4 = glm::vec4(lightPos[0], lightPos[1], lightPos[2], 1.0f);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	YRWindow myWindow("LearnOpenGL");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::string shaderFilesFolder = ".\\shader";
	std::string vertexShaderFilePath = shaderFilesFolder + "\\vshader.vert";
	std::string fragmentShaderFilePath = shaderFilesFolder + "\\fshader.frag";
	YRShader myshader(vertexShaderFilePath, fragmentShaderFilePath);

	std::string vertexShaderFilePath1 = shaderFilesFolder + "\\vshader2.vert";
	std::string fragmentShaderFilePath1 = shaderFilesFolder + "\\fshader2.frag";
	YRShader boxesShader(vertexShaderFilePath1, fragmentShaderFilePath1);

	std::string vertexShaderFilePath2 = shaderFilesFolder + "\\vshader2.vert";
	std::string fragmentShaderFilePath2 = shaderFilesFolder + "\\fshaderLight.frag";
	YRShader lightShader(vertexShaderFilePath2, fragmentShaderFilePath2);

	std::string textureFilesFolder = ".\\texture";
	std::string textureFilePath1 = textureFilesFolder + "\\container.jpg";
	std::string textureFilePath2 = textureFilesFolder + "\\awesomeface.png";
	YRTexture myTexture1(textureFilePath1.c_str());
	YRTexture myTexture2(textureFilePath2.c_str(), true, true);

	// unsigned int VBO1, VAO1, VBO2, VAO2;
	// glGenVertexArrays(1, &VAO1);
	// glGenBuffers(1, &VBO1);
	// glBindVertexArray(VAO1);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);
	// glGenVertexArrays(1, &VAO2);
	// glGenBuffers(1, &VBO2);
	// glBindVertexArray(VAO2);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// glEnableVertexAttribArray(0);

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesNormal), verticesNormal, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1); 

	unsigned int VBOTexture;
	glGenBuffers(1, &VBOTexture);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTexture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices36), vertices36, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOTexture);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//myshader.use();
	//myshader.setInt("texture1", 0);
	//myshader.setInt("texture2", 1);
	//boxesShader.use();
	//boxesShader.setInt("ourTexture", 0);
	//boxesShader.setVec3("lightPos", lightPos);

	glEnable(GL_DEPTH_TEST);

	while (!myWindow.ifCloseWindow())
	{
		myWindow.processInput(myWindow.window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear z-buffer

		glm::mat4 projection = glm::perspective(glm::radians(myCamera.m_Fov), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 view = myCamera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		lightShader.use();
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
		//lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		//lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
		//auto tempLightPosVec4 = model * lightPosVec4;
		//lightPos = glm::vec3(tempLightPosVec4[0], tempLightPosVec4[1], tempLightPosVec4[2]);

		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture1.texture);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, myTexture2.texture);


		boxesShader.use();
		auto objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
		auto lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		boxesShader.setVec3("objectColor", objectColor);
		boxesShader.setVec3("lightColor", lightColor);

		boxesShader.setMat4("projection", projection);
		boxesShader.setMat4("view", view);

		boxesShader.setVec3("viewPos", myCamera.m_Position);

		auto tempLightPosVec4 = model * lightPosVec4;
		auto k = glm::vec3(tempLightPosVec4[0], tempLightPosVec4[1], tempLightPosVec4[2]);
		boxesShader.setVec3("lightPos", k);

		 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
		boxesShader.setMat4("model", model);

		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//myshader.use();
		//glBindVertexArray(VAO);

		//for (size_t i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
		//{
		//	glm::mat4 model(1.0f);
		//	model = glm::translate(model, cubePositions[i]);
		//	float angle = 20.0f * (i + 1);
		//	if (i % 3 == 0)
		//	{
		//		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	}
		//	else
		//	{
		//		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		//	}
		//	myshader.setMat4("model", model);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}

		glfwSwapBuffers(myWindow.window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
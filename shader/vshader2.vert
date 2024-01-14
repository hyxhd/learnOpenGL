#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform float leftRightAdjust;
uniform float upDownAdjust;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    /*gl_Position =  transform * vec4(aPos.x + leftRightAdjust, 
aPos.y+upDownAdjust , aPos.z, 1.0);*/
    gl_Position = projection*view*model*vec4(aPos,1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    //ourColor = aColor;
    TexCoord = aTexCoord;
    Normal=aNormal;
}
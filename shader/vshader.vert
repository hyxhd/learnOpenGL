/*#version 330 core
layout (location = 0) in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0 
layout (location = 1) in vec3 aColor; // ��ɫ����������λ��ֵΪ 1

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ
out vec4 vecPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
    vecPos = gl_Position;
}*/

#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 TexCoord;

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
    //ourColor = aColor;
    TexCoord = aTexCoord;
}
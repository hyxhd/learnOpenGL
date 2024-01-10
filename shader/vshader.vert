/*#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0 
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1

out vec3 ourColor; // 向片段着色器输出一个颜色
out vec4 vecPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
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
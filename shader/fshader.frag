/*#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec4 vecPos;

void main()
{
    //FragColor = vec4(ourColor, 1.0);
    FragColor = vecPos;
}*/

#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float colorOffset;
uniform float colorAdjust;

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor.x, ourColor.y, ourColor.z+colorOffset, 1.0);
    //vec4 tempColor = vec4(ourColor.x, ourColor.y, ourColor.z+colorOffset, 1.0);
    vec2 tempTexCoord = vec2(-TexCoord.x, TexCoord.y);

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, tempTexCoord), colorAdjust);
    //FragColor = FragColor * tempColor;
}
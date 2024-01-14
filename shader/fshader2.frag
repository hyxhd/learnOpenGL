#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform vec3 lightPos;
uniform sampler2D ourTexture;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //vec3 result = ambient * objectColor;
    //FragColor = vec4(result, 1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    int glossy = 128;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), glossy);
    vec3 specular = specularStrength * spec * lightColor;

    /*float specularStrength = 0.8;
    int glossy = 256;
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 halfDirection = normalize(lightDir + viewDirection);
    vec3 specular = specularStrength * lightColor * pow(max(dot(Normal, halfDirection), 0.0), glossy);*/

    vec3 resultColor = (ambient + diffuse + specular) * objectColor;
    //vec3 resultColor = (ambient + diffuse) * objectColor;
    FragColor = texture(ourTexture, TexCoord) * vec4(resultColor, 1.0);

   // FragColor = vec4(resultColor, 1.0);
}
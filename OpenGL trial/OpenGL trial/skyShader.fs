#version 410 core
out vec4 FragColor;

in vec3 TexCoords1;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, TexCoords1);
}

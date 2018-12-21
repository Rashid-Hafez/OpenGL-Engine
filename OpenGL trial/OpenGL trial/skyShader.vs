#version 410 core
layout (location = 0) in vec3 position;

out vec3 TexCoords1; //using position coordinates as texture mapping coordinates, therefore we use vec3.

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords1 = position; //setting the texture as position!
    vec4 pos = projection * view * vec4(position,1.0);
    gl_Position = pos.xyww; //Z COORDINATE ISN'T USED FOR BACKGROUND IMAGES. W is the homogenous coordinate
}

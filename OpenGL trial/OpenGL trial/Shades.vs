#version 410 core

layout(location = 0) in vec4 position; //location 0, set in the "SHADER.CPP" //USED TO BE VEC3
layout(location = 1) in vec4 normal; //THIS WAS SET IN THE "SHADER.CPP" FILE. location 1
layout(location = 2) in vec2 texCoord; //set in the "shader.cpp"

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 MVP;

//variables to send out to the fragment
out vec2 texCoord0;
out vec4 normal0;
out vec4 FragPos;

void main(){

/*
 For normal vector we dont need to know the transformations of the object right now, so we use mat3(transpose(model)) to get the 3x3 matrix of the model
    we want the 3x3 not 4x4 because 3x3 has no informations on the transformations.
 
 This is some fancy sh!T:
 */
    vec3 normalT = mat3(transpose(inverse(model))) * vec3(normal.xyz); //Scale the normal with the model correctly corralating to world space
    
    
    FragPos = model * position; //send this fragment's position to the fragment shader
    normal0 = vec4(normalT,1.0); //send the normal coordinates to the fragment shader
    texCoord0 = texCoord;
    gl_Position = projection * view * model * FragPos; //used to be *vec4(position,1.0);

}

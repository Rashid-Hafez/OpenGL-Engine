//
//  Shader.cpp
//  OpenGL trial
//
//  This shader class was created with the help of BennyQBD tutorials.
//  https://github.com/BennyQBD/ModernOpenGLTutorial
//
//  Created by Rashid on 10/5/18.
//  Copyright © 2018 Rashid. All rights reserved.
//

#include "Shader.hpp"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& file){ //gets shader path
    
    ID = glCreateProgram();
    shaders[0] = CreateShader(LoadShader(file+".vs"), GL_VERTEX_SHADER); //vertex shader
    shaders[1] = CreateShader(LoadShader(file+".fs"), GL_FRAGMENT_SHADER); //fragment shader
    
    for(unsigned int i = 0; i < NUM_SHADERS; i++){
        glAttachShader(ID, shaders[i]); //attaches the shaders to your program
    }
    
    /*/ Tells the program how to read the attrib array. so we know all atributes with 0 is location/*/
    
    glBindAttribLocation(ID,0,"position"); //allocates space in the GPU. tells the GPU this space in the array only for position coordinates
    glBindAttribLocation(ID, 1, "normal");//allocates space in the GPU. tells the GPU this space in the array only for normal coordinates
    glBindAttribLocation(ID, 2, "textCoord");//allocates space in the GPU. tells the GPU this space in the array only for TEXTURE coordinates (VEC2)
    glBindAttribLocation(ID,3,"tangent");
    glBindAttribLocation(ID,4,"Bitangent");
    
    glLinkProgram(ID);
    CheckShaderError(ID, GL_LINK_STATUS, true,"Erorr Linking program bro!");
    
    glValidateProgram(ID);
    CheckShaderError(ID, GL_VALIDATE_STATUS, true,"Erorr program invalid bro!");
}

/*
 File reader for our shader
 */
std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());
    
    std::string output;
    std::string line;
    
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }
    
    return output;
}

/*
 Method to create shader.
 Returns: GLuint shader
    Returns the unsigned int which reffers to the shader created
 */
GLuint Shader::CreateShader(const std::string &text, unsigned int type){
    
    GLuint shader = glCreateShader(type);
    
    if(shader ==0){
        std::cerr << "Error compiling shader type " << type << std::endl;
    }
    
    const GLchar* p[1];
    p[0] = text.c_str(); //convert the shader string from a C++ string to a C string
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader); //complies shader, only need once every time you run the program
    
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
    return shader;
}


/*
    The most important method in this class.
    Must be called everytime in the main while loop.
 */
void Shader::Bind(){
    glUseProgram(ID);
}

/*
 Debugger
 */
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };
    
    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);
    
    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

/*
 Destructor
 */
Shader::~Shader(){
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(ID, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(ID);
}

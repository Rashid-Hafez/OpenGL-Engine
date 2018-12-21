//
//  Shader.hpp
//  OpenGL trial
//
//  Created by Rashid on 10/5/18.
//  https://github.com/BennyQBD/ModernOpenGLTutorial
//  Copyright © 2018 Rashid. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include <GL/glew.h>

class Shader{
public:
    Shader(const std::string& filename);//the filename containing the VS and FS
    void Bind(); //Sets the GPU to use the Fragment shader and Vertex shader assinged to this class
    virtual ~Shader();
    GLuint ID; //Variable that refers to the SHADER PROGRAM
    
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    
private:
    static const unsigned int NUM_SHADERS = 2; //Vertex shader, fragment shader and geometry shader
    //Shader(const Shader& other){}
    void operator =(const Shader& other){} //overloading the = operand, in CPP file this will take in a pointer for a shader and do some comparison
    
    std::string LoadShader(const std::string& file);
    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
    GLuint CreateShader(const std::string& text, unsigned int type);
    
    GLuint shaders[NUM_SHADERS];//makes an array to store the shader ints
};
#endif /* Shader_hpp */

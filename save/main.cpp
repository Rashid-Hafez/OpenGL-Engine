//
//  main.cpp
//  OpenGL trial
//
//  Created by Rashid on 9/28/18.
//  Copyright © 2018 Rashid. All rights reserved.
//
#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include "Model.hpp"
#include "Shader.hpp"
#include "mesh.hpp"
#include "obj_loader.hpp"

//////////////////////METHODS//////////////////////////////////////////
void hints();
int windowInit();
void render(double currentTime);
void setupRender();
void LoadCamera(GLuint programID);

//////////////////////VARIABLES//////////////////////////////////////////
GLFWwindow* window;
int width = 800;
int height = 600;
///CAMERA///////
glm::mat4 mvp;
glm::mat4 ModelMatrix;
glm::mat4 View;
glm::mat4 Projection;
unsigned int indicie[0];

///////////////////////////////////////////////////////////////////////////

int main() {
    
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    hints();
    if(windowInit()==-1){
        std::cout<<"Woah, error!";
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    std::cout<<"Loading Shader"<<std::endl;
    
    //SHADER VARIABLE
    Shader shader("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/OpenGL trial/OpenGL trial/Shades");
    
    //Model
    Model model1("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/OpenGL trial/nanosuit/nanosuit.obj");
    
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ){// Check if the ESC key was pressed or the window was closed
        
        double currentTime = glfwGetTime();
        glClear( GL_COLOR_BUFFER_BIT );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.Bind();
        
        
        LoadCamera(shader.ID);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
     glfwTerminate();
}

void render(double currentTime){
}

void hints(){
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
}

int windowInit(){
    // Open a window and create its OpenGL context
    
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    return 1;
}

void LoadCamera(GLuint programID){
    
    // Model matrix : an identity matrix (model will be at the origin)
    ModelMatrix = glm::mat4(1.0f);
    
    // Camera matrix (moving the world)
    View = glm::lookAt(
                       glm::vec3(0,2,3), // Camera is at (4,3,3), in World Space
                       glm::vec3(0,1,0), // and looks at the origin
                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                       );
    
    Projection = glm::perspective(glm::radians(50.0f), (float) width / (float)height, 0.1f, 100.0f);
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    mvp = Projection * View * ModelMatrix; // Remember, matrix multiplication is the other way around
    
    GLuint MatrixID = glGetUniformLocation(programID, "MVP"); //MVP IS UNIFORM VARIABLE IN SHADER
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
    
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

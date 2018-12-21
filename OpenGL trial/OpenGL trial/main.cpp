//
//  main.cpp
//  OpenGL trial
//
//  Created by Rashid on 9/28/18.
//  Copyright © 2018 Rashid. All rights reserved.
//
//  Multiple Obj
//  glm::mat4 model;
//  model = glm::translate(model, position);
//  float angle = 20.0f * i;
//  model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//  ourShader.setMat4("model", model);
//  glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include "Model.hpp"
#include "Shader.hpp"
#include "mesh.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"
//////////////////////METHODS//////////////////////////////////////////
void hints();
int windowInit();
void setupRender();
//void LoadCamera(GLuint programID);//Depreciated
void setCamera(GLuint programID, glm::vec3 translation, float angle, bool trans);
void processInput(GLFWwindow *window);
//////////////////////VARIABLES//////////////////////////////////////////
GLFWwindow* window;
int width = 1200;
int height = 800;
glm::mat4 mvp;
glm::mat4 ModelMatrix;
glm::mat4 View;
glm::mat4 Projection;
double currentTime;
float deltaTime;

/////////////////////////// LIGHT ////////////////////////////////////////////////
/** THE FOLLOWING VARIABLES ONLY DEFINE THE WORLD DIRECTIONAL LIGHT, THIS IS AN IMITATION OF THE SUN.  **/
glm::vec3       ia = glm::vec3(0.5, 0.5, 0.5); //aimbient color
GLfloat         ka = 0.3;
glm::vec3       id = glm::vec3(1.0, 1.0, 1.0); //diff color
GLfloat         kd = 0.5;
glm::vec3       is = glm::vec3(1.00f, 1.00f, 1.0f);
GLfloat         ks = 0.3;
GLfloat         shininess = 32.0f;
//glm::vec3 strD(0.1f); //Strength of the light diffuse Must convert to VEC4 when assigning as uniform att in shader
//glm::vec3 strS(100.0f); //Strength of the light specular Must convert to VEC4 when assigning as uniform att in shader
glm::vec3 lightPos;//DEFAULT STATIC GLOBAL LIGHT POSITION TRANSFORMATION VECTOR VARIABLE TO CATCH IN SHADER
glm::vec3 pLightPos = glm::vec3(10.0f,20.0f,10.0f); //Light position for point light
glm::vec3 pLightColour = glm::vec3(10.0f, 10.0f, 10.0f); //diff color
/////////////////////////// LIGHT ////////////////////////////////////////////////

/////////////////////////// CAMERA ////////////////////////////////////////////////
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2.0f;
float lastY = height / 2.0f;
bool firstMouse = true;
//methods:
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
/////////////////////////// CAMERA ////////////////////////////////////////////////

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
    } //opening wwindow
    
    //Mouse callbacks and moving the screen
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    std::cout<<"Loading Shader"<<std::endl;
    
//SHADER VARIABLE
Shader shader("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/OpenGL trial/OpenGL trial/Shades"); //Path for BOTH shaders
Shader lightShader("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/OpenGL trial/OpenGL trial/LightSource"); //shader for lightsource
Shader skyboxShader("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/OpenGL trial/OpenGL trial/skyShader");

    //environemnt//skybox
    Skybox* world;
    world = new Skybox();
    
//Model. SETUP BUFFER FIRST
// Model model1("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/modelA_Port.obj");
    Model model2("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/OpenGL trial/nanosuit/nanosuit.obj");
    Model cloth("/Users/rashid/Desktop/rash/1UNIVERSITY/Graphics/Model/tryPort.obj");
    Model light("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/cube.obj");
    Model lightP("/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/cube.obj");
    
    
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    
    glm::vec3 translate = glm::vec3(1.0,1.0,1.0);
    float angle = 0.1;
    
////////////////////////////////////    MAIN LOOP START   ///////////////////////////////////////////////////////////////
    while( glfwGetKey(window, GLFW_KEY_ESCAPE )
          !=
          GLFW_PRESS && glfwWindowShouldClose(window)
          ==
          0 ){// Check if the ESC key was pressed or the window was closed
        
        deltaTime = glfwGetTime();//gets the current milisecond float
        
        processInput(window);
        
        glEnable(GL_DEPTH_TEST);
        glClear( GL_COLOR_BUFFER_BIT );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear first
        
        
////////////////////NORMAL OBJECTS//////////////////////////// START
        shader.Bind(); //glUseProgram(shaderID)
        glUniform3f(glGetUniformLocation(shader.ID, "material.ia"), ia.r, ia.g, ia.b);
        glUniform1f(glGetUniformLocation(shader.ID, "sun.ka"), ka);
        glUniform3f(glGetUniformLocation(shader.ID, "material.id"), id.r,id.g,id.b); //diffuse colour, send to shader as id. aka lightcolour
        glUniform1f(glGetUniformLocation(shader.ID, "sun.kd"), kd);
        glUniform3f(glGetUniformLocation(shader.ID, "material.is"), is.r, is.g, is.b);
        glUniform1f(glGetUniformLocation(shader.ID, "sun.ks"), ks);
        glUniform1f(glGetUniformLocation(shader.ID, "material.shininess"), shininess);
        
        //pointlight
        glUniform3f(glGetUniformLocation(shader.ID, "pLight.is"), 1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(shader.ID, "pLight.id"), pLightColour.r,pLightColour.g,pLightColour.b);
        glUniform3f(glGetUniformLocation(shader.ID, "pLight.ia"), 0.05f,0.05f,0.05f);
        glUniform1f(glGetUniformLocation(shader.ID, "pLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shader.ID, "pLight.quadratic"), 0.09f);
        glUniform1f(glGetUniformLocation(shader.ID, "pLight.linear"), 0.32f);
        glUniform4f(glGetUniformLocation(shader.ID, "pLight.colour"), pLightColour.r,pLightColour.g,pLightColour.b,1.0);//TELL THE SHADER WHERE THE LIGHT

//        angle = angle * cos(deltaTime);
        
        setCamera(shader.ID,translate,angle,false); //Setup for object, need to refactor into method for arbitrary placement
        cloth.Draw(shader.ID);
        
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f,0.3f,0.3f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(5.0f, 0.75f, 0.0f));
        GLuint modelt = glGetUniformLocation(shader.ID, "model"); //model IS UNIFORM VARIABLE IN SHADER
        glUniformMatrix4fv(modelt, 1, GL_FALSE, &modelMatrix[0][0]);
        model2.Draw(shader.ID);
////////////////////////END NORMAL OBJECTS//////////////////////////// END
        
        //  L I G H T //
        float lightX = 0.0f;// * sin(deltaTime);
        float lightY = 150.0f;
        float lightZ = 150.5f;// * cos(deltaTime);
        lightPos = glm::vec3(lightX, lightY, lightZ);
        
        
        glUniform4f(glGetUniformLocation(shader.ID, "sun.lightPos"), -lightPos.x,-lightPos.y,-lightPos.z,0.0);//TELL THE SHADER WHERE THE LIGHT
        glUniform4f(glGetUniformLocation(shader.ID, "pLight.position"), pLightPos.x,pLightPos.y,pLightPos.z,1.0);//TELL THE SHADER WHERE THE LIGHT
        
        glUniform4f(glGetUniformLocation(shader.ID, "viewPos"), camera.Position.x,camera.Position.y,camera.Position.z,1.0);
        
        lightShader.Bind(); //glUseProgram(shaderID);
        
        glm::mat4 modelMatrixLIGHT = glm::mat4(1.0f);
        modelMatrixLIGHT = glm::scale(modelMatrixLIGHT, glm::vec3(0.05f,0.05f,0.05f));
        modelMatrixLIGHT = glm::translate(modelMatrixLIGHT, lightPos);//move to defined location
        GLuint modelL = glGetUniformLocation(lightShader.ID, "model"); //model IS UNIFORM VARIABLE IN SHADER
        glUniformMatrix4fv(modelL, 1, GL_FALSE, &modelMatrixLIGHT[0][0]);
        
        glm::mat4 projectionL = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
        GLuint proj = glGetUniformLocation(lightShader.ID, "projection"); //projection IS UNIFORM VARIABLE IN SHADER
        glUniformMatrix4fv(proj, 1, GL_FALSE, &projectionL[0][0]);
        
        glm::mat4 view = camera.GetViewMatrix();
        GLuint v = glGetUniformLocation(lightShader.ID, "view"); //view IS UNIFORM VARIABLE IN SHADER
        glUniformMatrix4fv(v, 1, GL_FALSE, &view[0][0]);
        
        light.Draw(shader.ID);
        
        modelMatrixLIGHT = glm::mat4(1.0f);
        modelMatrixLIGHT = glm::scale(modelMatrixLIGHT, glm::vec3(0.05f,0.05f,0.05f));
        modelMatrixLIGHT = glm::translate(modelMatrixLIGHT, pLightPos);//move to defined location
        GLuint modelLL = glGetUniformLocation(lightShader.ID, "model"); //model IS UNIFORM` VARIABLE IN SHADER
        glUniformMatrix4fv(modelLL, 1, GL_FALSE, &modelMatrixLIGHT[0][0]);
       
        
        float pX = 10.0f * sin(deltaTime);
        float pY = 15.0f +cos(deltaTime)+10.0f/tan(deltaTime)*sin(deltaTime); //10.0f is the offset
        float pZ = 10.0f * cos(deltaTime);
        pLightPos = glm::vec3(pX,pY,pZ);
        
        lightP.Draw(shader.ID);
        
        //END LIGHT
        
////////////////////    SKYBOX  //////////////////////////// START
glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    skyboxShader.Bind();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
            glUniformMatrix4fv((glGetUniformLocation(skyboxShader.ID,"view")),1,GL_FALSE,&view[0][0]);
            glUniformMatrix4fv((glGetUniformLocation(skyboxShader.ID,"projection")),1,GL_FALSE,&projectionL[0][0]);
                world->Draw();
glDepthFunc(GL_LESS); //Default requirements to pass the depth test.
        ////////////////////    SKYBOX  //////////////////////////// END
        
        
        //LoadCamera(shader.ID); Depreciated
      
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
     glfwTerminate();
}
/////////////////////////////////////   MAIN LOOP END   ///////////////////////////////////////////////////////////////////////////////

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


/**
    Mouse movement
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}
/**
    Mouse Scroll
 */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/**
 Self explanatory method.
 */
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   camera.ProcessKeyboard(Camera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   camera.ProcessKeyboard(Camera::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   camera.ProcessKeyboard(Camera::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   camera.ProcessKeyboard(Camera::RIGHT, deltaTime);
    
    
    //can also implement mechanical moving light, reacting to button press.
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)        lightPos.x -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)       lightPos.x += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)          lightPos.y += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)        lightPos.y -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)      lightPos.z -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)       lightPos.z += 0.1f;
    
                    //!!!!!!!DISCO DISCO!!!!!!!!!!!//
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) pLightColour.r -= 0.1f;
        if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) pLightColour.g -= 0.1f;
        if(glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) pLightColour.b -= 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        if (glfwGetKey(window, GLFW_KEY_X) != GLFW_PRESS) pLightColour.r += 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS){
        if (glfwGetKey(window, GLFW_KEY_X) != GLFW_PRESS) pLightColour.g += 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
        if (glfwGetKey(window, GLFW_KEY_X) != GLFW_PRESS) pLightColour.b += 0.1f;
    }
}

/**
 setCamera(); or setPosition();
 This method is to handle the MVP matrix layout for each object.
        Its not really a camera, just changing the matrices for each object assigned to each shader.
 -Parameters:
    -GLuint ID: this is for assigning the matrix to the shader you want.
    -translation: this is a VEC3 of a position you want the model to be stored in.
    -angle: the angle which you want to rotate an object by.
    -trans: if true then you want to translate the model, if false the model matrix is left as the identity matrix.
 **/
void setCamera(GLuint ID, glm::vec3 translation, float angle, bool trans){
    
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    
    GLuint proj = glGetUniformLocation(ID, "projection"); //projection IS UNIFORM VARIABLE IN SHADER
    glUniformMatrix4fv(proj, 1, GL_FALSE, &projection[0][0]);
    
    glm::mat4 view = camera.GetViewMatrix();
    GLuint viewI = glGetUniformLocation(ID, "view"); //view IS UNIFORM VARIABLE IN SHADER
    glUniformMatrix4fv(viewI, 1, GL_FALSE, &view[0][0]);
    
    glm::mat4 model(1.0f);
    
    if(trans){
        model = glm::translate(model, translation);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
    }
    else{
        model = glm::mat4(1.0f);
    }
    
    GLuint modelI = glGetUniformLocation(ID, "model"); //model IS UNIFORM VARIABLE IN SHADER
    glUniformMatrix4fv(modelI, 1, GL_FALSE, &model[0][0]);
}

/**
 Depreciated method.
 - See setCamera();
 //
 void LoadCamera(GLuint programID){
 
 // Model matrix : an identity matrix (model will be at the origin)
 ModelMatrix = glm::mat4(1.0f);
 
 // Camera matrix (moving the world)
 View = glm::lookAt(
 glm::vec3(0,1.5,0.5), // Camera is at (4,3,3), in World Space
 glm::vec3(0,1.5,0), // and looks at the origin
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
 **/

/*!!
 Major changes to program:
    Pre.A.1: Implemented camera class
    Pre.A.2: Implemented partial method to automate matrix adjustments in setCamera();
    Pre.A.3:
!!*/

//  Light.cpp
//  OpenGL trial
//
//  Created by Rashid on 11/26/18.
//  Copyright © 2018 Rashid. All rights reserved.
//
/**
 
 BROKEN IMPLEMENTATION
 
#include "Light.hpp"

Light::Light(float lightV[]){
    
    int size = sizeof(lightV)/sizeof(*lightV); //get the size of the object
    
    glGenVertexArrays(1, &LightVAO);
    glGenBuffers(1, &LightVBO);

    glBindVertexArray(LightVAO); //Open the box

     //load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, LightVBO);
     //A great thing about structs is that their memory layout is sequential for all its items.
    //The following code will split the GPU memory into sections to store IN ORDER: 0 position, 1 Normal, 2 Texture


    glBufferData(GL_ARRAY_BUFFER, sizeof(lightV), lightV, GL_STATIC_DRAW);

     //set the vertex attribute pointers

     //vertex Positions
    glEnableVertexAttribArray(0); //0 IS POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glBindVertexArray(1);
    
}

void Light::draw(){
    
        glBindVertexArray(LightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(1);

}

glm::vec3 Light::calcLights(){

    glm::vec3 trial;

    return trial;
}
**/

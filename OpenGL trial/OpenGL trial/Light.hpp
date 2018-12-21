//
//  Light.hpp
//  OpenGL trial
//
//  Created by Rashid on 11/26/18.
//  Copyright © 2018 Rashid. All rights reserved.
//
/**

 BROKEN IMPLEMENTATION
 
#ifndef Light_hpp
#define Light_hpp

#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>

using namespace std;

struct Vertex1 //structure to store our object DONT USE THE SAME NAME AS THE VERTEX STRUCT IN MESH
{
    glm::vec3 pos; //vec3 position (x,y,z)
    glm::vec2 texCoord; // Vec2 texture (p,q)
    glm::vec3 normal; //vec3(x,y,z)
};

class Light{
public:
    
    Light(float* lightV); //constructor
    glm::vec3 calcLights();
    /**
        Call draw only after you call the constructer for lights
    **/
//void draw();
//
//private:
//
//    GLuint LightVAO;//vertex array obj
//    GLuint LightVBO;
//    GLuint LightEBO;
//    unsigned int m_numIndices;
//
//    vector<Vertex1> lightVertices;
//    vector<unsigned int> lightIndices;
//};
//
//
//#endif /* Light_hpp */

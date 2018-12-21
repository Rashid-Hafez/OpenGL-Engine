//
//  mesh.cpp
//  OpenGL trial
//
/*
 This class will let us create either a mesh from our vertex points or create a mesh given an obj file
 
    The mesh class is responsible for setting up the buffers on the GPU and binding the buffers to our array buffers.
    It will tell the GPU how to process the data we give it and how to read the vertex attributes and what to draw, either static or otherwise.
*/
//  Created by Rashid on 10/5/18.
//  Copyright © 2018 Rashid. All rights reserved.

#include "mesh.hpp"

/*
 * Lets render the mesh, given the indexed model
 */
Mesh::Mesh(const std::string& File){
    InitMesh(OBJModel(File).ToIndexedModel());
}



void Mesh::InitMesh(const IndexedModel & model){
    m_numIndices = model.indices.size();
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(NUM_BUFFERS, VBO);
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int),
                 &model.indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glBindVertexArray(0);
    
    //add clothes
}

/*
 * Lets render the mesh, given vectors of attributes...
 */
Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices){
    
    m_numIndices = numVertices;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(NUM_BUFFERS, &VAO); //generate the amount of bufferes needed for the arrays.
    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferData(GL_ARRAY_BUFFER,numVertices*sizeof(vertices[0]),vertices,GL_STATIC_DRAW); //Putting all our verticies into this massive array.
    
    glEnableVertexAttribArray(0);//Divides data into attributes, but still keeps sequential array full of points the GPU can read. Tells GPU how to read the array of attributes
    
    
    /*Tells the program how to read our list of attributes,*/
    glVertexAttribPointer(
                           0,                  // attribute 0, must be same in shader AND PREVIOUS LINE IS 0 MUST BE SAME! this tells us we want to use the shader with location 0 for this object
                           3,                  // dealing with vec3 so 3 points of data
                           GL_FLOAT,           // type
                           GL_FALSE,           // normalized?
                           0,                  // stride
                           (void*)0            // array buffer offset
                           );
    
    glBindVertexArray(0); //this will not allow you to edit the vertex array of '0' after this line, therefore its commented out for later use
}

void Mesh::Draw(){
    glBindVertexArray(VAO);
    
    //glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, m_numIndices);
    
    glBindVertexArray(0);
}

Mesh::~Mesh(){
    //glDeleteVertexArrays(1,&VAO);
}

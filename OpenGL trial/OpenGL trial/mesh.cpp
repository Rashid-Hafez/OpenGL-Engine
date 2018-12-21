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

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
    
    meshVertices = vertices;
    meshIndices = indices;
    meshTextures = textures;
    
    InitMesh();
}


// THIS IS DONE ONCE FOR EACH OBJECT
void Mesh::InitMesh(){
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    //
    glBindVertexArray(VAO); //Open the box
    
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    //The following code will split the GPU memory into sections to store IN ORDER: 0 position, 1 Normal, 2 Texture
    
    
    glBufferData(GL_ARRAY_BUFFER, meshVertices.size() * sizeof(Vertex), &meshVertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //different to array_buffer, element array buffer is INDEXED, stores all the correct indicies
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshIndices.size() * sizeof(unsigned int), &meshIndices[0], GL_STATIC_DRAW); //INDEXED malloc
    
    // set the vertex attribute pointers
    
    // vertex Positions
    glEnableVertexAttribArray(0); //0 IS POSITION
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    // vertex normals
    glEnableVertexAttribArray(1); //1 IS NORMAL
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    
    // vertex tangent, ASSIMP LOADER NEEDS
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    
    // vertex bitangent, ASSIMP LOADER NEEDS
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    
    glBindVertexArray(0);
}


//CALLED IN REALTIME
void Mesh::Draw(GLuint shaderID){
   
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < meshTextures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = meshTextures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream
        
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, meshTextures[i].tID);
    }
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(1);
    
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

Mesh::~Mesh(){
    //glDeleteVertexArrays(1,&VAO);
}

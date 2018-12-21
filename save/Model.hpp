//
//  Model.hpp
//  OpenGL trial
//
//  Created by Rashid on 11/6/18.
//  Copyright © 2018 Rashid. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>


#include "mesh.hpp"
#include "Shader.hpp"


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Model{
public:
    
    Model(string const &path);
    
private:
    
    vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<mesh> meshes;
    string directory;
    
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif /* Model_hpp */

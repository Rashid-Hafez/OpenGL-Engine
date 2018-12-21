//
//  Skybox.hpp
//  OpenGL trial
//
//  Created by Rashid on 11/28/18.
//  Copyright © 2018 Rashid. All rights reserved.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <stdio.h>
#include <glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <GL/glew.h>

class Skybox{

public:
    Skybox(); //constructor
        void Draw();
        GLuint getTexID();
        std::vector<std::string> getFaces();
    
private:
    
GLuint loadSkybox(); //Method to load the textures from storage.
        GLuint skyboxVAO;
        GLuint skyboxVBO;
        GLuint cubemapTexture;
    
    std::vector<std::string> faces
    {
        "/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/Skybox/right.jpg",
        "/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/Skybox/left.jpg",
        "/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/Skybox/up.jpg", //roof
        "/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/Skybox/down.jpg", //floor
        "/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/Skybox/front.jpg",
        "/Users/rashid/Desktop/rash/1WORKSPACE/Uni/Graphics/Res/Skybox/back.jpg"
    };
};
#endif /* Skybox_hpp */

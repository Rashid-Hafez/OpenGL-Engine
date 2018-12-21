//
//  camera.hpp
//  OpenGL trial
//
//  Created by Rashid on 11/16/18.
//  Copyright © 2018 Rashid. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include <stdio.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods


class Camera{
    
public:
    
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;
    
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    //Keyboard
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    //
    
    Camera(glm::vec3 position);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    void ProcessMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);
     void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    glm::mat4 GetViewMatrix();
    
    
private:
    void updateCameraVectors();
};


#endif /* camera_hpp */

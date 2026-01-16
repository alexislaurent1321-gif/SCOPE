#include "SCOPE/camera.h"
#include <algorithm>
#include <iostream>

Camera::Camera()
    : Position{cameraDefault::Position},
      Target{cameraDefault::Target},
      up{cameraDefault::up},
      RotationCenter{0.f},
      nearPlane{cameraDefault::nearPlane},
      farPlane{cameraDefault::farPlane},
      fov{cameraDefault::fov},
      aspectRatio{cameraDefault::aspectRatio}
{
    updateCameraOrientation();
}

void Camera::pan(float dx, float dy){

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), (-dx*right - dy*up) * glm::distance(Position, RotationCenter));
    Position = translate * glm::vec4(Position, 1.0f);
    Target = translate * glm::vec4(Target, 1.0f);
}

void Camera::rotate(float dx, float dy){

    float newPitch = glm::clamp(pitch + dy, glm::radians(-89.f), glm::radians(89.f));
    yaw -= dx;

    float allowedPitch = newPitch - pitch;
    pitch = newPitch;

    glm::quat qYaw = glm::angleAxis(-dx, cameraDefault::up);
    glm::quat qPitch = glm::angleAxis(allowedPitch, right);
    glm::quat arcRotate =  qYaw * qPitch;

    Position = RotationCenter + arcRotate * (Position - RotationCenter);
    Target = RotationCenter + arcRotate * (Target - RotationCenter);

    updateCameraOrientation();
}

void Camera::zoom(float dz){
    float distance = glm::distance(Position, RotationCenter);
    Position = glm::translate(glm::mat4(1.0f), -dz * front * glm::distance(Position, Target)) * glm::vec4(Position, 1.0f);
}

void Camera::zoom(float dz, float xpos, float ypos){
    float shift = dz * tan(glm::radians(fov/2));
    pan(-xpos * shift, ypos * shift);

    zoom(dz);
}

void Camera::zoom(float dz, float mouseX, float mouseY, float depth, const glm::vec4& viewport){
    glm::vec3 worldPosition = glm::unProject({mouseX, viewport[3]-mouseY, depth}, getViewMatrix(), getProjectionMatrix(), viewport);
    
    // Direction of the zoom
    glm::vec3 direction = worldPosition - Position;
    auto distance = glm::length(direction);

    direction = glm::normalize(direction);

    // Zoom to this point (camera movement + target)
    Position += direction * dz * distance;
    Target += direction * dz * distance;

    // RotationCenter = worldPosition;
    Target = Position - glm::distance(Position, RotationCenter) * front;
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(Position, Target, up);
}

glm::mat4 Camera::getProjectionMatrix() const{
    auto rightPlane = tan(glm::radians(fov/2)) * aspectRatio;
    auto upPlane = tan(glm::radians(fov/2));

    switch(projection){
        case PERSPECTIVE : 
            rightPlane *= nearPlane;
            upPlane *= nearPlane;
            return glm::frustum(-rightPlane, rightPlane, -upPlane, upPlane, nearPlane, farPlane);
            break;
        case ORTHOGRAPHIC : 
            float distance = glm::distance(Position, Target);
            rightPlane *= distance;
            upPlane *= distance;
            return glm::ortho(-rightPlane, rightPlane, -upPlane, upPlane, nearPlane, farPlane);
            break;
    }    
}

void Camera::updateCameraOrientation(){
    up = cameraDefault::up;
    front = glm::normalize(Position - Target);
    right = glm::normalize(glm::cross(up, front));
    up = glm::cross(front, right);   
}




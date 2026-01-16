#include "SCOPE/cameraController.h"
#include <glad/glad.h>


CameraController::CameraController(Camera& camera_) : camera(camera_) {}


void CameraController::ProcessMouseZoom(float dz){
    camera.zoom(dz);
}

void CameraController::ProcessMouseRotate(float dx, float dy){
    dx *= rotateSensitivity;
    dy *= rotateSensitivity;

    camera.rotate(dx, dy);
}

void CameraController::ProcessMousePan(float dx, float dy){
    dx *= panSensitivity;
    dy *= panSensitivity;

    camera.pan(dx, dy);
}

void CameraController::ProcessMouseScrollAtCursor(float dz, float mouseX, float mouseY, float screenWidth, float screenHeight)
{
    dz *= zoomSensitivity;

    if(!zoomToCursor){
        camera.zoom(dz);
        return;
    }

    glm::vec4 viewport(0.f, 0.f, screenWidth, screenHeight);

    float depth;
    glReadPixels((int)mouseX, viewport[3]-(int)mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    bool processZoomDepth = depth < 1.f;
    if(processZoomDepth){
        camera.zoom(dz, mouseX, mouseY, depth, viewport);
    }
    else{
        // cursor position into homogenneous space
        float x_screen = ((mouseX / screenWidth) * 2 - 1) * camera.aspectRatio;
        float y_screen = ((mouseY / screenHeight) * 2 - 1);
        camera.zoom(dz, x_screen, y_screen);
    }  
}

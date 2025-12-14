#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "camera.h"


class CameraController {
public:
    Camera camera;

    float rotateSensitivity = 0.01f;
    float panSensitivity = 0.001f;
    float zoomSensitivity = 0.1f;

    bool zoomToCursor = true;

    CameraController() = default;
    CameraController(Camera& camera_);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseZoom(float dz);

    void ProcessMouseRotate(float dx, float dy);

    void ProcessMousePan(float dx, float dy);

    void ProcessMouseScrollAtCursor(float dz, float mouseX, float mouseY, float screenWidth, float screenHeight);
};
#endif

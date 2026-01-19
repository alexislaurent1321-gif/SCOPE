#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "SCOPE/camera.h"

namespace SCOPE {

    class Camera;

/**
 * @brief This class contains variables for the user interface into the UIcamera class as well as methods for the input manager into the context class
 */
class CameraController {
public:
    Camera camera;

    float rotateSensitivity = 0.01f;        ///< sensitivity of the rotation
    float panSensitivity = 0.001f;          ///< sensitivity of the pan
    float zoomSensitivity = 0.1f;        ///< sensitivity of the zoom

    bool zoomToCursor = true;            ///< true if the zoom is done to the cursor position

    /**
     * @brief Default constructor
     */
    CameraController() = default;

    /**
     * @brief Constructor by giving a camera
     * 
     * @param camera_ 
     */
    CameraController(Camera& camera_);

    /**
     * @brief Process the zoom with zoomSensibility for the input manager
     * 
     * @param dz displacement on the z axis by scrolling
     */
    void ProcessMouseZoom(float dz);

    /**
     * @brief Process the zoom with zoomSensibility for the input manager
     * 
     * @param dz displacement on the z axis by scrolling
     * @param mouseX x position in the screen space
     * @param mouseY y position in the screen space 
     * @param screenWidth width of the screen by pixels
     * @param screenHeight height of the screen by pixels
     */
    void ProcessMouseScrollAtCursor(float dz, float mouseX, float mouseY, float screenWidth, float screenHeight);

    /**
     * @brief Process the rotation with rotateSensibility for the input manager
     * 
     * @param dx displacement on the x axis for the yaw
     * @param dy displacement on the y axis for the pitch
     */
    void ProcessMouseRotate(float dx, float dy);

    /**
     * @brief Process the pan with panSensitibility for the input manager
     * 
     * @param dx displacement on the x axis
     * @param dy displacement on the y axis
     */
    void ProcessMousePan(float dx, float dy);

};

}

#endif

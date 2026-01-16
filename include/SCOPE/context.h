#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>
#include "SCOPE/cameraController.h"


#include <iostream>

const unsigned int SCR_HEIGHT = 600;    // Default screen size

/**
 * @brief Class to initialize a window and manage the inputs
 */
class Context {
public:
    GLFWwindow* window;                                         // pointer to a GLFW window (GLFW is programmed in C)
    CameraController cameraController;                          // camera controller called by the inputs managed by the context
    float aspectRatio = cameraController.camera.aspectRatio;    // aspect ratio to define the screen width by multiplying the screen height

    float lastX = SCR_HEIGHT * aspectRatio / 2.0f;      // x cursor position of the last frame in centered screen space
    float lastY = SCR_HEIGHT / 2.0f;                    // y cursor position of the last frame in centered screen space

    float cursorX = SCR_HEIGHT * aspectRatio / 2.0f;    // x cursor position of the current frame in centered screen space
    float cursorY = SCR_HEIGHT / 2.0f;                  // y cursor position of the current frame in centered screen space

    bool firstMouse = true;             // true if the mouse is moving
    bool leftButtonDown = false;        // true if the left button is  down
    bool rightButtonDown = false;       // true if the right button is down
    bool middleButtonDown = false;      // true if the middle button is down

    /**
     * @brief Default constructor of the context
     */
    Context();

    /**
     * @brief Init the context by using the input manager
     */
    void init();


    /**
     * @brief Actions by press a mouse button
     * 
     * @param window pointer to the window
     * @param button indicates which button is pressed
     * @param action indicates which action is performed depending on the button used
     */
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    /**
     * @brief Compute the displacement of the mouse in screen space between the last frame and the current frame
     * 
     * @param window pointer to the window
     * @param mouseX x position in the screen space
     * @param mouseY y position in the screen space 
     */
    static void mouse_callback(GLFWwindow* window, double mouseX, double mouseY);

    /**
     * @brief 
     */
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    
    static void processInput(GLFWwindow* window, float deltaTime);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif
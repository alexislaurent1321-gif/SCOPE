#ifndef CONTEXT_H
#define CONTEXT_H

#include <GLFW/glfw3.h>
#include "cameraController.h"


#include <iostream>

// settings
const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = SCR_HEIGHT * 16. / 9.;

class Context {
public:
    GLFWwindow* window;
    CameraController cameraController;

    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;

    // Position actuelle du curseur
    float cursorX = SCR_WIDTH / 2.0f;
    float cursorY = SCR_HEIGHT / 2.0f;

    bool firstMouse = true;
    bool leftButtonDown = false;
    bool rightButtonDown = false;
    bool middleButtonDown = false;

    Context();

    void init();

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    // 🔹 Callbacks statiques (compatibles C)
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    // 🔹 Entrées clavier
    static void processInput(GLFWwindow* window, float deltaTime);

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif
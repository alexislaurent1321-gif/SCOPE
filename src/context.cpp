#include "SCOPE/context.h"

Context::Context() : window(nullptr), cameraController() {} 

void Context::init() {

    // Initialisation de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow((int) (SCR_HEIGHT * aspectRatio), SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // Associating the Context object with the GLFW window
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);


    // Tell GLFW to capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Context::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));
    if (!context) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT)
        context->leftButtonDown = (action == GLFW_PRESS);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        context->rightButtonDown = (action == GLFW_PRESS);
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        context->middleButtonDown = (action == GLFW_PRESS);
}

void Context::mouse_callback(GLFWwindow* window, double mouseX, double mouseY) {

    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));
    if (!context) return;

    float xpos = static_cast<float>(mouseX);
    float ypos = static_cast<float>(mouseY);

    if (context->firstMouse) {
        context->lastX = xpos;
        context->lastY = ypos;
        context->firstMouse = false;
    }

    float xoffset = xpos - context->lastX;
    float yoffset = context->lastY - ypos;

    context->lastX = xpos;
    context->lastY = ypos;

    if (context->leftButtonDown)
        context->cameraController.ProcessMouseRotate(xoffset, yoffset);
    else if (context->rightButtonDown)
        context->cameraController.ProcessMousePan(xoffset, yoffset);    
}

void Context::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));

    if (context)
    context->cameraController.ProcessMouseScrollAtCursor(static_cast<float>(yoffset),
                                                    context->lastX,
                                                    context->lastY,
                                                    (int) (SCR_HEIGHT * context->cameraController.camera.aspectRatio),
                                                    SCR_HEIGHT);
}

void Context::processInput(GLFWwindow* window, float deltaTime) {
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Context::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    // glViewport(0, 0, width, height);
}
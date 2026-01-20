#ifndef SCOPE_H
#define SCOPE_H

#include "SCOPE/model/datas/VBO.h"
#include "SCOPE/model/datas/VAO.h"
#include "SCOPE/model/datas/texture.h"
#include "SCOPE/model/model.h"

#include "SCOPE/shader.h"
#include "SCOPE/light.h"

#include "SCOPE/UIs/UICamera.h"
#include "SCOPE/UIs/UILight.h"
#include "SCOPE/UIs/UIModel.h"
#include "SCOPE/UIs/UIManager.h"

#include "SCOPE/context/context.h"
#include "SCOPE/context/scene.h"


namespace SCOPE{

    /**
     * @brief Initialize OpenGL 
     * 
     */
    int init(){
        // Loading of openGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        // Depth test
        glEnable(GL_DEPTH_TEST); 
    }

    /**
     * @brief Shutdown GLFW
     * 
     */
    void shutDown(){
        glfwTerminate();
    }

}

#endif
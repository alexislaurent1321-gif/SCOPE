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

#include "SCOPE/context/context.h"
#include "SCOPE/context/scene.h"



namespace SCOPE{

    /**
     * @brief Initialize OpenGL 
     * 
     */
    int openGL_init(){
        // Loading of openGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        // Depth test
        glEnable(GL_DEPTH_TEST); 
    }

    /**
     * @brief Initialize IMGUI
     * 
     * @param context 
     */
    void UI_init(Context context){
        // Initialization of IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(context.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    /**
     * @brief Update IMGUI frame
     * 
     */
    void UI_update(){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /**
     * @brief Render IMGUI frame
     * 
     */
    void UI_render(){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    /**
     * @brief Shutdown IMGUI
     * 
     */
    void UI_shutDown(){
        // End of IMGUI
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
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
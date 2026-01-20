#ifndef SCOPE_UIMANAGER_H
#define SCOPE_UIMANAGER_H

#include "SCOPE/UIs/UILight.h"
#include "SCOPE/UIs/UIModel.h"
#include "SCOPE/UIs/UICamera.h"

namespace SCOPE {

/**
 * @brief Class to manage all the UIs
 */
class UIManager {

    UILight uiLight;    ///< UI for the lights
    UIModel uiModel;    ///< UI for the model
    UICameraController uiCamera;    ///< UI for the camera controller

public: 
    
    /**
     * @brief Draw all the UIs
     * 
     * @param scene 
     * @param context 
     */
    void draw(SCOPE::Scene& scene, SCOPE::Context& context){ 
        update();

        uiLight.draw(scene);
        uiModel.draw(scene);
        uiCamera.draw(context);

        render();
    }

    /**
     * @brief Initialize IMGUI
     * 
     * @param context 
     */
    void init(Context context){
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
    void update(){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /**
     * @brief Render IMGUI frame
     * 
     */
    void render(){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    /**
     * @brief Shutdown IMGUI
     * 
     */
    void shutDown(){
        // End of IMGUI
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

};

}

#endif 

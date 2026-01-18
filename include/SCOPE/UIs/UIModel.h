#ifndef UIMODEL_H
#define UIMODEL_H

#include "SCOPE/model/model.h"
#include "SCOPE/context/scene.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

/**
 * @brief User interface to manage a chosen model in the scene
 */
class UIModel{

private : 
    glm::vec3 UIPosition{0.f};
    glm::vec3 UIOrientation{0.f};
    glm::vec3 UIScale{1.f};

public : 
    // Model* model = nullptr;

    bool show = true;
    UIModel() = default;

    void draw(Scene* scene){
    if(!(scene->getModel())) return;

    if(ImGui::Begin("Model Inspector", &show)){
        
        ImGui::Text("Paramètres du modèle");
        ImGui::Separator();

        // Transform
        if(ImGui::CollapsingHeader("Transformations", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if(ImGui::DragFloat3("Position", glm::value_ptr(UIPosition), 0.1f, -100.f, 100.f, "%.2f"))
                scene->getModel()->setPosition(UIPosition);
            
            if(ImGui::DragFloat3("Rotation", glm::value_ptr(UIOrientation), 0.5f, -360.f, 360.f, "%.1f deg"))
                scene->getModel()->setOrientation(UIOrientation);
            
            if(ImGui::DragFloat3("Échelle", glm::value_ptr(UIScale), 0.01f, 0.001f, 100.f))
                scene->getModel()->setScale(UIScale);

            if(ImGui::Button("Reset Transform")){
                UIPosition = {0.f, 0.f, 0.f};
                UIOrientation = {0.f, 0.f, 0.f};
                UIScale = {1.f, 1.f, 1.f};
                scene->getModel()->setPosition({0.f, 0.f, 0.f}); 
                scene->getModel()->setOrientation({0.f, 0.f, 0.f});
                scene->getModel()->setScale({1.f, 1.f, 1.f});
            }
        }
    }
    ImGui::End();
}

};

#endif
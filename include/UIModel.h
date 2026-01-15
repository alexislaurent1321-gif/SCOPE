#ifndef UIMODEL_H
#define UIMODEL_H

#include "model.h"
#include <imgui.h>

/**
 * \brief User interface to manage a chosen model in the scene
 */
class UIModel{

private : 
    glm::vec3 UIPosition{0.f};
    glm::vec3 UIOrientation{0.f};
    glm::vec3 UIScale{1.f};

public : 
    Model* model = nullptr;

    bool show = true;
    UIModel() = default;
    UIModel(Model* model_) : model(model_) {};

    void draw(){
    if(!model) return;

    if(ImGui::Begin("Model Inspector", &show)){
        
        ImGui::Text("Paramètres du modèle");
        ImGui::Separator();

        // Transform
        if(ImGui::CollapsingHeader("Transformations", ImGuiTreeNodeFlags_DefaultOpen))
        {
            if(ImGui::DragFloat3("Position", glm::value_ptr(UIPosition), 0.1f, -100.f, 100.f, "%.2f"))
                model->setPosition(UIPosition);
            if(ImGui::DragFloat3("Rotation", glm::value_ptr(UIOrientation), 0.5f, -360.f, 360.f, "%.1f deg"))
                model->setOrientation(UIOrientation);
            if(ImGui::DragFloat3("Échelle", glm::value_ptr(UIScale), 0.01f, 0.001f, 100.f))
                model->setScale(UIScale);

            if(ImGui::Button("Reset Transform")){
                model->setPosition({0.f, 0.f, 0.f}); 
                model->setOrientation({0.f, 0.f, 0.f});
                model->setScale({1.f, 1.f, 1.f});
            }
        }

        // Infos
        if(ImGui::CollapsingHeader("Informations")){
            ImGui::Text("Adresse mémoire : %p", model);
        }
    }
    ImGui::End();
}

};

#endif
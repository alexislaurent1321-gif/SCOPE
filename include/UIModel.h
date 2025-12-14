#ifndef UIMODEL_H
#define UIMODEL_H

#include "model.h"
#include <imgui.h>

class UIModel{
public : 
    Model* model = nullptr;

    bool show = true;
    UIModel() = default;
    UIModel(Model* model_) : model(model_) {};

    void DrawUI(){
        if(ImGui::Begin("Model", &show))
        {
            ImGui::Text("Model stteings");
            ImGui::Separator();

            // ----- Movement / Rotation -----
            ImGui::SliderFloat("Position", &model->position.x, -10.f, 10.f);
            ImGui::DragFloat3("Orientation", &model->orientation.x, 10.f);
            ImGui::DragFloat3("Mise à l'échelle", &model->size.x, 10.f);
        }

        ImGui::End();
    }
};

#endif
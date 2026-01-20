#ifndef UILIGHT_H
#define UILIGHT_H

#include "SCOPE/light.h"
#include "SCOPE/context/scene.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>
#include <memory>

namespace SCOPE {

    class Scene;

/**
 * @brief User interface to manage lights in the scene
 */
class UILight {
public:

    UILight() = default;

    // ImGui Interface 
    void draw(Scene& scene) {

        ImGui::Begin("Lights");

        if (ImGui::Button("Add point light")){
            PointLight pointLight;
            scene.add(pointLight);
        }

        ImGui::SameLine();
        
        if (ImGui::Button("Add directional light")){
            DirLight dirLight;
            scene.add(dirLight);
        }

        ImGui::Separator();

        for (int i=0; i < scene.getPointLights().size(); ++i) {

            auto &entry = scene.getPointLights()[i];
            std::string label = "point light " + std::to_string(i);

            if (ImGui::CollapsingHeader(label.c_str())) {

                // Delete button
                if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())) {
                    scene.getPointLights().erase(scene.getPointLights().begin() + i);
                    --i;
                    continue;
                }

                drawUI(*(scene.getPointLights()[i]));
            }
        }

        for (int i=0; i < scene.getDirLights().size(); ++i) {

            auto &entry = scene.getDirLights()[i];
            std::string label = "directional light " + std::to_string(i);

            if (ImGui::CollapsingHeader(label.c_str())) {

                // Delete button
                if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())) {
                    scene.getDirLights().erase(scene.getDirLights().begin() + i);
                    --i;
                    continue;
                }

                drawUI(*(scene.getDirLights()[i]));
            }
        }

        ImGui::End();
    }

    // UI for each types of light

    void drawUI(PointLight &l) {
        ImGui::Text("point light");
        ImGui::DragFloat3("position", &l.position.x, 0.1f);
        ImGui::ColorEdit3("ambient", &l.ambient.x);
        ImGui::ColorEdit3("diffuse", &l.diffuse.x);
        ImGui::ColorEdit3("specular", &l.specular.x);

        ImGui::DragFloat("constant", &l.constant, 0.01f);
        ImGui::DragFloat("linear", &l.linear, 0.01f);
        ImGui::DragFloat("quadratic", &l.quadratic, 0.01f);
    }

    void drawUI(DirLight &l) {
        ImGui::Text("directional light");
        ImGui::DragFloat3("direction", &l.direction.x, 0.1f);
        ImGui::ColorEdit3("ambient", &l.ambient.x);
        ImGui::ColorEdit3("diffuse", &l.diffuse.x);
        ImGui::ColorEdit3("specular", &l.specular.x);
    }
};

}

#endif

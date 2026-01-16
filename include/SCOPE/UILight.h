#ifndef UILIGHT_H
#define UILIGHT_H

#include "SCOPE/light.h"
#include <imgui.h>
#include <vector>
#include <memory>

/**
 * \brief User interface to manage lights in the scene
 */
class UILight {
public:
    enum class LightType{Point, Directional};   

    struct LightEntry {
        LightType type;
        std::unique_ptr<Light> light;
    };

    std::vector<LightEntry> lights;

    UILight() = default;

    // Put a light
    void addLight(LightType type) {
        LightEntry entry;
        entry.type = type;

        if (type == LightType::Point)
            entry.light = std::make_unique<PointLight>();
        else if (type == LightType::Directional)
            entry.light = std::make_unique<DirLight>();

        lights.push_back(std::move(entry));
    }

    // ImGui Interface 
    void draw() {
        ImGui::Begin("Lights");

        if (ImGui::Button("Ajouter PointLight"))
            addLight(LightType::Point);
        ImGui::SameLine();
        if (ImGui::Button("Ajouter DirectionalLight"))
            addLight(LightType::Directional);

        ImGui::Separator();

        for (int i = 0; i < lights.size(); ++i) {
            auto &entry = lights[i];
            std::string label = "Light " + std::to_string(i);

            if (ImGui::CollapsingHeader(label.c_str())) {

                // Delete button
                if (ImGui::Button(("Delete##" + std::to_string(i)).c_str())) {
                    lights.erase(lights.begin() + i);
                    --i;
                    continue;
                }

                if (entry.type == LightType::Point) {
                    drawPointLightUI(*static_cast<PointLight*>(entry.light.get()));
                }
                else if (entry.type == LightType::Directional) {
                    drawDirectionalLightUI(*static_cast<DirLight*>(entry.light.get()));
                }
            }
        }

        ImGui::End();
    }

    // UI for each types of light

    void drawPointLightUI(PointLight &l) {
        ImGui::Text("PointLight");
        ImGui::DragFloat3("Position", &l.position.x, 0.1f);
        ImGui::ColorEdit3("Ambient", &l.ambient.x);
        ImGui::ColorEdit3("Diffuse", &l.diffuse.x);
        ImGui::ColorEdit3("Specular", &l.specular.x);

        ImGui::DragFloat("Constant", &l.constant, 0.01f);
        ImGui::DragFloat("Linear", &l.linear, 0.01f);
        ImGui::DragFloat("Quadratic", &l.quadratic, 0.01f);
    }

    void drawDirectionalLightUI(DirLight &l) {
        ImGui::Text("DirectionalLight");
        ImGui::DragFloat3("Direction", &l.direction.x, 0.1f);
        ImGui::ColorEdit3("Ambient", &l.ambient.x);
        ImGui::ColorEdit3("Diffuse", &l.diffuse.x);
        ImGui::ColorEdit3("Specular", &l.specular.x);
    }
};

#endif

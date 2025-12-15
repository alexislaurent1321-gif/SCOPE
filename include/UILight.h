#ifndef UILIGHT_H
#define UILIGHT_H

#include "light.h"
#include <imgui.h>
#include <vector>
#include <memory>

class UILight {
public:
    enum class LightType{Point, Directional, Spot};

    struct LightEntry {
        LightType type;
        std::unique_ptr<Light> light;
    };

    std::vector<LightEntry> lights;

    UILight() = default;

    // Ajouter une lumière
    void addLight(LightType type) {
        LightEntry entry;
        entry.type = type;

        if (type == LightType::Point)
            entry.light = std::make_unique<PointLight>();
        else if (type == LightType::Directional)
            entry.light = std::make_unique<DirLight>();
        else if (type == LightType::Spot)
            entry.light = std::make_unique<SpotLight>();

        lights.push_back(std::move(entry));
    }

    // Interface ImGui
    void draw() {
        ImGui::Begin("Lights");

        if (ImGui::Button("Ajouter PointLight"))
            addLight(LightType::Point);
        ImGui::SameLine();
        if (ImGui::Button("Ajouter DirectionalLight"))
            addLight(LightType::Directional);
        ImGui::SameLine();
        if (ImGui::Button("Ajouter SpotLight"))
            addLight(LightType::Spot);

        ImGui::Separator();

        for (int i = 0; i < lights.size(); ++i) {
            auto &entry = lights[i];
            std::string label = "Light " + std::to_string(i);

            if (ImGui::CollapsingHeader(label.c_str())) {

                // Bouton supprimer
                if (ImGui::Button(("Supprimer##" + std::to_string(i)).c_str())) {
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
                else if (entry.type == LightType::Spot) {
                    drawSpotLightUI(*static_cast<SpotLight*>(entry.light.get()));
                }
            }
        }

        ImGui::End();
    }

    // ----- UI de chaque type de lumière -----

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

    void drawSpotLightUI(SpotLight &l) {
        ImGui::Text("SpotLight");
        ImGui::DragFloat3("Position", &l.position.x, 0.1f);
        ImGui::DragFloat3("Direction", &l.direction.x, 0.1f);

        ImGui::ColorEdit3("Ambient", &l.ambient.x);
        ImGui::ColorEdit3("Diffuse", &l.diffuse.x);
        ImGui::ColorEdit3("Specular", &l.specular.x);

        ImGui::DragFloat("Constant", &l.constant, 0.01f);
        ImGui::DragFloat("Linear", &l.linear, 0.01f);
        ImGui::DragFloat("Quadratic", &l.quadratic, 0.01f);

        ImGui::DragFloat("CutOff", &l.cutOff, 0.01f);
        ImGui::DragFloat("OuterCutOff", &l.outerCutOff, 0.01f);
    }
};

#endif

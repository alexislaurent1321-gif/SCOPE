#ifndef UICAMERA_H
#define UICAMERA_H

#include "cameraController.h"
#include <imgui.h>

class UICameraController
{
public:
    CameraController* cameraController = nullptr;
    bool show = true;

    UICameraController() = default;
    UICameraController(CameraController* cameraController_) : cameraController(cameraController_) {}

    void DrawUI()
    {
        if(!cameraController || !show)
            return;

        if(ImGui::Begin("Camera cameraController", &show))
        {
            ImGui::Text("Camera Settings");
            ImGui::Separator();

            // ----- Movement / Rotation -----
            ImGui::SliderFloat("Rotate Sensitivity", &cameraController->rotateSensitivity, 0.0001f, 0.02f);
            ImGui::SliderFloat("Pan Sensitivity", &cameraController->panSensitivity, 0.0001f, 0.01f);
            ImGui::SliderFloat("Zoom Sensitivity", &cameraController->zoomSensitivity, 0.01f, 1.0f);

            // ---- Options ----
            ImGui::Checkbox("Zoom to Cursor", &cameraController->zoomToCursor);
            // ImGui::Checkbox("Orthographic projection", &cameraController->camera.projectionortho);


            ImGui::Spacing();
            ImGui::SliderFloat("FOV", &cameraController->camera.fov, 30.f, 90.f);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Text("Camera Debug Info:");
            ImGui::Spacing();

            // display useful information
            ImGui::Text("Position:  %.3f  %.3f  %.3f",
                        cameraController->camera.Position.x,
                        cameraController->camera.Position.y,
                        cameraController->camera.Position.z);

            ImGui::Text("Target:    %.3f  %.3f  %.3f",
                        cameraController->camera.Target.x,
                        cameraController->camera.Target.y,
                        cameraController->camera.Target.z);

            ImGui::Text("Up:        %.3f  %.3f  %.3f",
                        cameraController->camera.up.x,
                        cameraController->camera.up.y,
                        cameraController->camera.up.z);

            ImGui::Text("FOV:       %.2f", cameraController->camera.fov);
            ImGui::Text("Aspect:    %.2f", cameraController->camera.aspectRatio);
            
            ImGui::Text("Near/Far:  %.2f / %.2f",
                        cameraController->camera.nearPlane,
                        cameraController->camera.farPlane);

            ImGui::Spacing();
            ImGui::Separator();

            // Reset button
            if(ImGui::Button("Reset Camera"))
            {
                cameraController->camera = Camera();
            }
        }

        ImGui::End();
    }
};

#endif
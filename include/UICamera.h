#ifndef UICAMERA_H
#define UICAMERA_H

#include "cameraController.h"
#include <imgui.h>

/**
 * \brief class allowing control of the camera via ImGui
 */
class UICameraController
{
public:
    CameraController* cameraController = nullptr;   // this class control the values of the controller
    bool show = true;                               // we see the ImGui window if true

    /**
     * \brief Default constructor
     */
    UICameraController() = default;

    /**
     * \brief Constructor with an existing controller
     * 
     * \param cameraController_ existing controller 
     */
    UICameraController(CameraController* cameraController_) : cameraController(cameraController_) {}

    /**
     * \brief Draw the content of the UI
     */
    void draw()
    {
        if(!cameraController || !show)
            return;

        if(ImGui::Begin("Camera cameraController", &show))
        {
            ImGui::Text("Camera Settings");
            ImGui::Separator();

            // Rotation, pan, zoom sensitivities
            ImGui::SliderFloat("Rotate Sensitivity", &cameraController->rotateSensitivity, 0.0001f, 0.02f);
            ImGui::SliderFloat("Pan Sensitivity", &cameraController->panSensitivity, 0.0001f, 0.01f);
            ImGui::SliderFloat("Zoom Sensitivity", &cameraController->zoomSensitivity, 0.01f, 1.0f);

            // Zoom to cursor if true
            ImGui::Checkbox("Zoom to Cursor", &cameraController->zoomToCursor);
            // ImGui::Checkbox("Orthographic projection", &cameraController->camera.projectionortho);


            ImGui::Spacing();
            ImGui::SliderFloat("FOV", &cameraController->camera.fov, 30.f, 90.f);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Text("Camera Debug Info:");
            ImGui::Spacing();

            // Display useful informations
            ImGui::Text("Position:  %.3f  %.3f  %.3f",
                        cameraController->camera.Position.x,
                        cameraController->camera.Position.y,
                        cameraController->camera.Position.z);

            ImGui::Text("Target:    %.3f  %.3f  %.3f",
                        cameraController->camera.Target.x,
                        cameraController->camera.Target.y,
                        cameraController->camera.Target.z);

            ImGui::Text("up:        %.3f  %.3f  %.3f",
                        cameraController->camera.up.x,
                        cameraController->camera.up.y,
                        cameraController->camera.up.z);

            ImGui::Text("FOV:       %.2f", cameraController->camera.fov);
            ImGui::Text("aspect ratio :    %.2f", cameraController->camera.aspectRatio);
            
            ImGui::Text("near/far:  %.2f / %.2f",
                        cameraController->camera.nearPlane,
                        cameraController->camera.farPlane);

            ImGui::Spacing();
            ImGui::Separator();

            // Reset button
            if(ImGui::Button("Reset camera"))
            {
                cameraController->camera = Camera();
            }
        }

        ImGui::End();
    }
};

#endif
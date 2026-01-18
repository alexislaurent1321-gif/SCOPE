#ifndef UICAMERA_H
#define UICAMERA_H

#include "SCOPE/context/context.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

/**
 * @brief class allowing control of the camera via ImGui
 */
class UICameraController
{
public:
    bool show = true;                               // we see the ImGui window if true

    /**
     * @brief Default constructor
     */
    UICameraController() = default;

    /**
     * @brief Draw the content of the UI
     */
    void draw(Context& context)
    {
        if(!(&(context.cameraController) || !show))
            return;

        if(ImGui::Begin("Camera cameraController", &show))
        {
            ImGui::Text("Camera Settings");
            ImGui::Separator();

            // Rotation, pan, zoom sensitivities
            ImGui::SliderFloat("rotate Sensitivity", &context.cameraController.rotateSensitivity, 0.0001f, 0.02f);
            ImGui::SliderFloat("pan Sensitivity", &context.cameraController.panSensitivity, 0.0001f, 0.01f);
            ImGui::SliderFloat("zoom Sensitivity", &context.cameraController.zoomSensitivity, 0.01f, 1.0f);

            // Zoom to cursor if true
            ImGui::Checkbox("zoom to Cursor", &context.cameraController.zoomToCursor);
            // ImGui::Checkbox("Orthographic projection", &cameraController->camera.projectionortho);

            ImGui::SliderFloat("FOV", &context.cameraController.camera.fov, 30.f, 90.f);

            // Reset button
            if(ImGui::Button("reset camera"))
                context.cameraController.camera = Camera();

        }

        ImGui::End();
    }
};

#endif
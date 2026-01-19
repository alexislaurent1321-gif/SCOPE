#ifndef UICAMERA_H
#define UICAMERA_H

#include "SCOPE/context/context.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace SCOPE {

/**
 * @brief Class to create a UI for the camera controller
 */
class UICameraController
{
public:
    bool show = true;                ///< true if the UI is shown

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

            toggleEnum(context);

            ImGui::SliderFloat("FOV", &context.cameraController.camera.fov, 30.f, 90.f);

            // Reset button
            if(ImGui::Button("reset camera"))
                context.cameraController.camera = Camera();

        }

        ImGui::End();
    }

    /**
     * @brief Toggle the projection enum between perspective and orthographic
     * 
     * @param context 
     */
    void toggleEnum(Context& context){
        bool persp = (context.cameraController.camera.projection == PERSPECTIVE);
        if(ImGui::Checkbox("Perspective", &persp)){
            context.cameraController.camera.projection = persp ? PERSPECTIVE : ORTHOGRAPHIC;
        }
    }
};

}

#endif
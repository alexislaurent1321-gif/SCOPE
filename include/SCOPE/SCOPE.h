#include "SCOPE/model/datas/VBO.h"
#include "SCOPE/model/datas/VAO.h"
#include "SCOPE/model/datas/texture.h"
#include "SCOPE/shader.h"
#include "SCOPE/context/context.h"
#include "SCOPE/light.h"
#include "SCOPE/model/model.h"

#include "SCOPE/UIs/UICamera.h"
#include "SCOPE/UIs/UILight.h"
#include "SCOPE/UIs/UIModel.h"

namespace SCOPE{

    void UI_init(Context context){
        // Initialization of IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(context.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void UI_update(Context context){
        // Initialization of IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(context.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");  
    }

    void UI_render(){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UI_shutDown(){
        // End of IMGUI
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

}
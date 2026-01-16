#include <iostream>
#include <vector>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "SCOPE/VBO.h"
#include "SCOPE/VAO.h"
#include "SCOPE/texture.h"
#include "SCOPE/shader.h"
#include "SCOPE/context.h"
#include "SCOPE/light.h"
#include "SCOPE/model.h"

#include "SCOPE/UICamera.h"
#include "SCOPE/UILight.h"
#include "SCOPE/UIModel.h"


// Frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(){
    
    // Initialisation de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Context creation
    Context context;
    context.init();

    // Loading of openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Camera& camera = context.cameraController.camera;


    // Depth test
    glEnable(GL_DEPTH_TEST); 

    // Initialization of IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(context.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Shaders loading
    // Shader shader1("resources/shaders/model_loading.vert", "resources/shaders/model_loading.frag");
    Shader shader1("resources/shaders/lights.vert", "resources/shaders/lights.frag");
    // Shader cubeLightShader("resources/shaders/light_cube.vert", "resources/shaders/light_cube.frag");

    // Models loading
    Model model1("resources/models/backpack2/scene.gltf");
    // Model model1("resources/models/backpack/backpack.obj");


    // -----------------------------
    //  Render loop
    // -----------------------------
    
    UICameraController uiCam(&context.cameraController);
    UIModel uiModel(&model1);
    UILight uiLight;

    while (!glfwWindowShouldClose(context.window))
    {
        // Updating frames
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Call to the input manager
        context.processInput(context.window, deltaTime);

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader1.use();
        shader1.setUniform("viewPos", camera.Position);
        float shininess = 1.;
        shader1.setUniform("material.shininess", shininess);


        int pointIndex = 0, dirIndex = 0, spotIndex = 0;

        for (auto &entry : uiLight.lights) {
            if (entry.type == UILight::LightType::Point){
                static_cast<PointLight*>(entry.light.get())->apply(shader1, pointIndex++);
                const int nbPointLights = pointIndex;
                shader1.setUniform("nbPointLights", nbPointLights);
            }
            else if (entry.type == UILight::LightType::Directional){
                static_cast<DirLight*>(entry.light.get())->apply(shader1, dirIndex++);
                const int nbDirLights = dirIndex;
                shader1.setUniform("nbDirLights", nbDirLights);
            }
        }

        // Space transformations for the vertex shader
        glm::mat4 projection = camera.getProjectionMatrix();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 model = model1.getModelMatrix();

        shader1.setUniform("projection", projection);
        shader1.setUniform("view", view);
        shader1.setUniform("model", model);
        model1.draw(shader1);

        // UI update
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        uiCam.draw();
        uiLight.draw();
        uiModel.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }

    // End of IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}

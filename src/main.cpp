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

#include "VBO.h"
#include "VAO.h"
#include "texture.h"
#include "shader.h"
#include "context.h"
#include "light.h"
#include "model.h"

#include "UICamera.h"
#include "UILight.h"
#include "UIModel.h"


// Frame
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main(){
    
    // Initialisation de GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Création du contexte
    Context context;
    context.init();

    // Chargement d'openGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Camera& camera = context.cameraController.camera;


    // Test de profondeur
    glEnable(GL_DEPTH_TEST); 

    // Initialisation d'IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(context.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // // Chargement des shaders
    // Shader shader1("resources/shaders/model_loading.vert", "resources/shaders/model_loading.frag");
    Shader shader1("resources/shaders/lights.vert", "resources/shaders/lights.frag");
    Shader cubeLightShader("resources/shaders/light_cube.vert", "resources/shaders/light_cube.frag");

    // Chargement des modèles
    Model model1("resources/models/backpack2/scene.gltf");
    // Model model1("resources/models/backpack/backpack.obj");


    // -----------------------------
    //  Boucle de rendu
    // -----------------------------
    UICameraController uiCam(&context.cameraController);
    UIModel uiModel(&model1);
    UILight uiLight;

    while (!glfwWindowShouldClose(context.window))
    {
        // Actualisation des frames
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Appel du gestionnaire d'inputs
        context.processInput(context.window, deltaTime);

        // Rendu
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
            // else if (entry.type == UILight::LightType::Spot)
            //     static_cast<SpotLight*>(entry.light.get())->apply(shader1, spotIndex++);
        }

        // Transformations d'espace pour le vertex shader
        glm::mat4 projection = camera.getProjectionMatrix();
        glm::mat4 view = camera.getViewMatrix();
        // glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 model = model1.getModelMatrix();

        shader1.setUniform("projection", projection);
        shader1.setUniform("view", view);
        shader1.setUniform("model", model);
        model1.draw(shader1);

        cubeLightShader.use();
        model = glm::translate(model, glm::vec3(0.f, 2.f, 0.f));
        cubeLightShader.setUniform("projection", projection);
        cubeLightShader.setUniform("view", view);
        cubeLightShader.setUniform("model", model);

        // Actualisation de l'UI
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

    // Fin d'IMGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}

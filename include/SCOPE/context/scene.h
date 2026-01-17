#ifndef SCENE_H
#define SCENE_H

#include "SCOPE/SCOPE.h"
#include <vector>
#include <memory>
#include <string>

// namespace SCOPE {

// Forward declarations to avoid unnecessary inclusions
class Model;
class Light;
class Camera;
class Shader;

class Scene {
public:
    Scene();

    // Adding elements to the scene
    void addLight(std::shared_ptr<Light> light){
        lights.push_back(light);
    }
    void setCamera(std::shared_ptr<Camera> camera_){
        camera = camera_;
    }
    void setModel(std::shared_ptr<Model> model_){
        model = model_;
    }

    // Scene render
    void render(Shader shader){

        // Updating frames
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Call to the input manager
        context.processInput(context.window, deltaTime);

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setUniform("viewPos", camera->Position);
        float shininess = 1.;
        shader.setUniform("material.shininess", shininess);


        int pointIndex = 0, dirIndex = 0, spotIndex = 0;

        for (auto &entry : uiLight.lights) {
            if (entry.type == UILight::LightType::Point){
                static_cast<PointLight*>(entry.light.get())->apply(shader, pointIndex++);
                const int nbPointLights = pointIndex;
                shader.setUniform("nbPointLights", nbPointLights);
            }
            else if (entry.type == UILight::LightType::Directional){
                static_cast<DirLight*>(entry.light.get())->apply(shader, dirIndex++);
                const int nbDirLights = dirIndex;
                shader.setUniform("nbDirLights", nbDirLights);
            }
        }

        // Space transformations for the vertex shader
        shader.setUniform("projection", camera->getProjectionMatrix());
        shader.setUniform("view", camera->getViewMatrix());
        shader.setUniform("model", model->getModelMatrix());
        model->draw();

        // UI update
        SCOPE::UI_update();

        uiCam.draw();
        uiLight.draw();
        uiModel.draw();

        SCOPE::UI_render();

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }

    // Update the image
    void update(float deltaTime){

    }

    // getters
    std::shared_ptr<Model> getModel() const{
        return model;
    }

    const std::vector<std::shared_ptr<Light>>& getLights() const{
        return lights;
    }

    std::shared_ptr<Camera> getCamera() const{
        return camera;
    }

private:
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Model> model;
};

// } 

#endif

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

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setUniform("viewPos", camera->Position);
        float shininess = 1.;
        shader.setUniform("material.shininess", shininess);

        // Space transformations for the vertex shader
        shader.setUniform("projection", camera->getProjectionMatrix());
        shader.setUniform("view", camera->getViewMatrix());
        shader.setUniform("model", model->getModelMatrix());
        model->draw(shader);
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

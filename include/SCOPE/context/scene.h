#ifndef SCENE_H
#define SCENE_H

#include "SCOPE/SCOPE.h"
#include <vector>
#include <memory>
#include <string>
#include <typeinfo>

// namespace SCOPE {

// // Forward declarations to avoid unnecessary inclusions
// class Model;
// class Light;
// class Camera;
// class Shader;

class Scene {
public:
    Scene(){}

    // Adding elements to the scene
    void add(PointLight light){
        pointLights.push_back(std::make_shared<PointLight>(light));
    }
    void add(DirLight light){
        dirLights.push_back(std::make_shared<DirLight>(light));
    }
    void setCamera(Camera camera_){
        camera = std::make_shared<Camera>(camera_);
    }
    void setModel(Model model_){
        model = std::make_shared<Model>(model_);
    }

    // Scene render
    void render(Context& context, Shader& shader){

        *camera = context.cameraController.camera;
        if(!camera) return;

        // Render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setUniform("viewPos", camera->Position);
        shader.setUniform("material.shininess", 1.f);

        // Space transformations for the vertex shader
        shader.setUniform("projection", camera->getProjectionMatrix());
        shader.setUniform("view", camera->getViewMatrix());
        shader.setUniform("model", model->getModelMatrix());
        model->draw(shader);

        for (int i=0; i<pointLights.size(); i++){
            pointLights[i]->apply(shader, i);
        }
        shader.setUniform("nbPointLights", (int) pointLights.size());

        for (int i=0; i<dirLights.size(); i++){
            dirLights[i]->apply(shader, i);
        }
        shader.setUniform("nbDirLights", (int) dirLights.size());
    }

    // getters
    std::shared_ptr<Model> getModel() const{
        return model;
    }

    std::vector<std::shared_ptr<PointLight>> getPointLights() const{
        return pointLights;
    }

    std::vector<std::shared_ptr<DirLight>> getDirLights() const{
        return dirLights;
    }

    std::shared_ptr<Camera> getCamera() const{
        return camera;
    }

private:
    std::vector<std::shared_ptr<PointLight>> pointLights;
    std::vector<std::shared_ptr<DirLight>> dirLights;
    std::shared_ptr<Camera> camera = nullptr;
    std::shared_ptr<Model> model = nullptr;
};

// } 

#endif

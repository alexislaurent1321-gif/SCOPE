#include "SCOPE/context/scene.h"

namespace SCOPE {

// Adding elements to the scene
void Scene::add(PointLight light){
    pointLights.push_back(std::make_shared<PointLight>(light));
}
void Scene::add(DirLight light){
    dirLights.push_back(std::make_shared<DirLight>(light));
}
void Scene::setCamera(Camera camera_){
    camera = std::make_shared<Camera>(camera_);
}
void Scene::setModel(Model model_){
    model = std::make_shared<Model>(model_);
}

void Scene::update(Context& context){
    // Call to the input manager
    context.processInput(context.window);
    glfwSwapBuffers(context.window);
    glfwPollEvents();
}

// Scene render
void Scene::render(Context& context, Shader& shader){

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
std::shared_ptr<Model> Scene::getModel() const{
    return model;
}

std::vector<std::shared_ptr<PointLight>> Scene::getPointLights() const{
    return pointLights;
}

std::vector<std::shared_ptr<DirLight>> Scene::getDirLights() const{
    return dirLights;
}

std::shared_ptr<Camera> Scene::getCamera() const{
    return camera;
}


} 
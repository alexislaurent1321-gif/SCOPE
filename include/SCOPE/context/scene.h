#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>

namespace SCOPE {

// Forward declarations to avoid unnecessary inclusions
class Model;
class Light;
class Camera;
class Shader;

class Scene {
public:
    Scene();

    // Adding elements to the scene
    void addModel(std::shared_ptr<Model> model){
        models.push_back(model);
    }
    void addLight(std::shared_ptr<Light> light){
        lights.push_back(light);
    }
    void setCamera(std::shared_ptr<Camera> camera_){
        camera = camera_;
    }

    // Scene render
    void render(){
        // update shader 


    }

    // Update the image
    void update(float deltaTime);

    // getters
    const std::vector<std::shared_ptr<Model>>& getModels() const{
        return models;
    }

    const std::vector<std::shared_ptr<Light>>& getLights() const{
        return lights;
    }

    std::shared_ptr<Camera> getCamera() const{
        return camera;
    }

private:
    std::vector<std::shared_ptr<Model>> models;
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> camera;
};

} 

#endif

#ifndef SCENE_H
#define SCENE_H

#include "SCOPE/light.h"
#include "SCOPE/model/model.h"
#include "SCOPE/context/context.h"

#include <vector>
#include <memory>
#include <string>
#include <typeinfo>

namespace SCOPE {

/**
 * @brief Represents a scene in the 3D rendering pipeline.
 * 
 */
class Scene {
public:
    Scene() = default;

    /**
     * @brief Adding point light to the scene
     * @param light 
     */
    void add(PointLight light);

    /**
     * @brief Adding directional lights to the scene
     * @param light   
     */
    void add(DirLight light);

    /** @brief Sets the camera for the scene
     * @param camera_
     */
    void setCamera(Camera camera_);

    /** @brief Sets the model for the scene
     * @param model_
     */
    void setModel(Model model_);

    /**
     * @brief Update the scene with the context
     * 
     * @param context 
     */
    void update(Context& context);

    /**
     * @brief Render the scene with the context and the shader
     * 
     * @param context 
     * @param shader 
     */
    void render(Context& context, Shader& shader);
    
    // getters
    std::shared_ptr<Model> getModel() const;

    std::vector<std::shared_ptr<PointLight>> getPointLights() const;

    std::vector<std::shared_ptr<DirLight>> getDirLights() const;

    std::shared_ptr<Camera> getCamera() const;

private:
    std::vector<std::shared_ptr<PointLight>> pointLights; ///< list of point lights in the scene
    std::vector<std::shared_ptr<DirLight>> dirLights;    ///< list of directional lights in the scene
    std::shared_ptr<Camera> camera = nullptr;               ///< camera of the scene
    std::shared_ptr<Model> model = nullptr;              ///< model of the scene
};

} 

#endif

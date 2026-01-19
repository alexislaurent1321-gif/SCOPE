#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SCOPE/shader.h"

namespace SCOPE {

/**
 * @brief Abstract class to represent a light with its common attributes
 */
class Light {
public:
    glm::vec3 ambient{0.1f};    
    glm::vec3 diffuse{1.0f};
    glm::vec3 specular{1.0f};

    /**
     * @brief Default constructor
     */
    Light() = default;

    /**
     * @brief Constructor with general light parameters
     * 
     * @param ambient_ ambient light
     * @param diffuse_ diffuse light
     * @param specular_ specular light
     */
    Light(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);

    /**
     * @brief Abstract method to send the light to a shader
     * 
     * @param shader shader used
     * @param index index of the light
     * @param name name of the light
     */
    virtual void apply(Shader& shader, int index, const std::string& name) const = 0;
};



/**
 * @brief Derived class of Light. Uniform illumination in all directions with attenuation
 */
class PointLight : public Light{
    public : 
    glm::vec3 position{0.f, 0.f, 1.f};      // light position

    float constant = 0.5f;      // constant coefficient
    float linear = 0.09;        // linear attenuation coefficient
    float quadratic = 0.032;    // quadratic attenuation coefficient

    /**
     * @brief Default constructor of PointLight
     */
    PointLight() = default;  
    
    /**
     * @brief Contructor of PointLight with given position
     * 
     * @param position_
     */
    PointLight(glm::vec3 position_);

    /**
     * @brief Contructor of PointLight with given position and abstract light attributes
     * 
     * @param position_ 
     * @param ambient_
     * @param diffuse_
     * @param specular_
     */
    PointLight(glm::vec3 position_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);

    /**
     * @brief Contructor of PointLight with given position, abstract light attributes and attenuation coefficient
     * 
     * @param position_ 
     * @param ambient_
     * @param diffuse_
     * @param specular_
     * @param constant
     * @param linear_
     * @param quadratic_
     */
    PointLight(glm::vec3 position_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, float constant_, float linear_, float quadratic_);

    /**
     * @brief send the spot light to a shader
     * 
     * @param shader shader used
     * @param index index of the light
     * @param name name of the light
     */
    void apply(Shader& shader, int index, const std::string& name = "pointLights") const override;
};



/**
 * @brief Derived class of Light. Light in a single direction without attenuation
 */
class DirLight : public Light{
    public : 
    glm::vec3 direction{0.f, 0.f, 1.f}; // direction of the light

    /**
     * @brief Default constructor of DirLight
     */
    DirLight() = default;

    /**
     * @brief Constructor of Dirlight by a given direction
     * 
     * @param direction_
     */
    DirLight(glm::vec3 direction_);

    /**
     * @brief Construction of Dirlight by given direction and abstract light attributes
     * 
     * @param direction_
     * @param ambient_
     * @param diffuse_
     * @param specular_
     */
    DirLight(glm::vec3 direction_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);

    /**
     * @brief Send the directional light to a shader
     * 
     * @param shader shader used
     * @param index index of the light
     * @param name name of the light
     */
    void apply(Shader& shader, int index, const std::string& name = "dirLights") const override;
};

}

#endif
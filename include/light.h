#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Light {
public:
    glm::vec3 ambient{0.1f};
    glm::vec3 diffuse{1.0f};
    glm::vec3 specular{1.0f};

    Light() = default;
    Light(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);

    virtual void apply(Shader& shader, int index, const std::string& name) const = 0;
};


class PointLight : public Light{
    public : 
    glm::vec3 position{0.f, 0.f, 1.f};

    float constant = 0.5f;
    float linear = 0.09;
    float quadratic = 0.032;  

    PointLight() = default;
    PointLight(glm::vec3 position_);
    PointLight(glm::vec3 position_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);
    PointLight(glm::vec3 position_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, float constant_, float linear_, float quadratic_);

    void apply(Shader& shader, int index, const std::string& name = "pointLights") const override;
};

class DirLight : public Light{
    public : 
    glm::vec3 direction{0.f, 0.f, 1.f};

    DirLight() = default;
    DirLight(glm::vec3 direction_);
    DirLight(glm::vec3 direction_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);

    void apply(Shader& shader, int index, const std::string& name = "dirLights") const override;
};

class SpotLight : public Light{
     public : 
    glm::vec3 position{0.f, 0.f, 1.f};
    glm::vec3 direction{0.f, 0.f, 1.f};

    float constant = 1.;
    float linear = 0.09;
    float quadratic = 0.032;  

    float cutOff;
    float outerCutOff;

    SpotLight() = default;
    SpotLight(glm::vec3 direction_);
    SpotLight(glm::vec3 direction_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_);

    void apply(Shader& shader, int index, const std::string& name = "spotLights") const override;
};
#endif
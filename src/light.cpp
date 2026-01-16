#include "SCOPE/light.h"


Light::Light(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_) : 
ambient(ambient_),
diffuse(diffuse_),
specular(specular_)
{}


// Point light

PointLight::PointLight(glm::vec3 position_) 
: position(position_) {}

PointLight::PointLight(glm::vec3 position_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_) 
: position(position_), Light(ambient_, diffuse_, specular_) {}

PointLight::PointLight(glm::vec3 position_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, float constant_, float linear_, float quadratic_) 
: position(position_), Light(ambient_, diffuse_, specular_), constant(constant_), linear(linear_), quadratic(quadratic_) {}


void PointLight::apply(Shader& shader, int index, const std::string& name) const{
    
    std::string pointLight_str = name + "[" + std::to_string(index) + "]";  // 

    shader.setUniform(pointLight_str + ".position", position);
    shader.setUniform(pointLight_str + ".ambient", ambient);
    shader.setUniform(pointLight_str + ".diffuse", diffuse);
    shader.setUniform(pointLight_str + ".specular", specular);

    shader.setUniform(pointLight_str + ".constant", constant);
    shader.setUniform(pointLight_str + ".linear", linear);
    shader.setUniform(pointLight_str + ".quadratic", quadratic);
}


// Directional light

DirLight::DirLight(glm::vec3 direction_) 
: direction(direction_) {}
DirLight::DirLight(glm::vec3 direction_, glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_) 
: direction(direction_), Light(ambient_, diffuse_, specular_) {}

void DirLight::apply(Shader& shader, int index, const std::string& name) const {
    
    std::string dirLight_str = name + "[" + std::to_string(index) + "]";

    shader.setUniform(dirLight_str + ".direction", direction);
    shader.setUniform(dirLight_str + ".ambient", ambient);
    shader.setUniform(dirLight_str + ".diffuse", diffuse);
    shader.setUniform(dirLight_str + ".specular", specular);
}


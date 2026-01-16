#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "SCOPE/Texture.h"
#include "SCOPE/Shader.h"

class Material {
public:
    glm::vec3 diffuseColor{1.0f};
    glm::vec3 specularColor{1.0f};
    float shininess = 32.0f;

    Texture* diffuseTexture = nullptr;
    Texture* specularTexture = nullptr;

    void bind(const Shader& shader) const;
};

#endif
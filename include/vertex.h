#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

/**
 * @brief Vertex datas which contains position, UV, normal, tangent and bitangent datas
 */
struct Vertex{
    glm::vec3 position;
    glm::vec2 UV;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

#endif
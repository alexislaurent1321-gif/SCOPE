#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace SCOPE {

/**
 * @brief Structure to represent a vertex with its attributes
 */
struct Vertex{
    glm::vec3 position; ///< position of the vertex
    glm::vec2 UV;      ///< texture coordinates of the vertex
    glm::vec3 normal;   ///< normal vector of the vertex
    glm::vec3 tangent;  ///< tangent vector of the vertex
    glm::vec3 bitangent;        ///< bitangent vector of the vertex
};

}

#endif
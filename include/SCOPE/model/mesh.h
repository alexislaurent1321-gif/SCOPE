#ifndef MESH_H
#define MESH_H

#include "SCOPE/model/datas/vertex.h"
#include "SCOPE/shader.h"

#include "SCOPE/model/datas/texture.h"
#include "SCOPE/model/datas/VAO.h"
#include "SCOPE/model/datas/VBO.h"
#include "SCOPE/model/datas/EBO.h"

#include <vector>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SCOPE {
 
/**
 * @brief Class to represent a mesh with its datas and methods to draw it
 * 
 */
class Mesh
{
    public : 
    std::vector<Vertex> vertices;  ///< vertex datas
    std::vector<Index> indices;     ///< index datas
    std::vector<Texture> textures;  ///< textures/materials

    /**
     * @brief Constructor by giving the vertices, indices and textures of the mesh
     * 
     * @param vertices_ 
     * @param indices_ 
     * @param textures_ 
     */
    Mesh(std::vector<Vertex> vertices_, std::vector<GLuint> indices_, std::vector<Texture> textures_);

    /**
     * @brief Draw the mesh by binding appropriate textures and drawing the elements
     * 
     * @param shader 
     */
    void draw(Shader& shader);

    /**
     * @brief Get the model matrix of the mesh
     * 
     * @return glm::mat4 
     */
    glm::mat4 getModelMatrix();

    /**
     * @brief Set the model matrix of the mesh
     * 
     * @param modelMatrix_ 
     */
    void setModelMatrix(const glm::mat4& modelMatrix_);

    private : 
    
    VAO VAO;                  ///< Vertex Array Object    
    glm::mat4 modelMatrix;  ///< model matrix

    /**
     * @brief Setup the mesh (create buffers and arrays)
     * 
     */
    void setup();     
};

}

#endif
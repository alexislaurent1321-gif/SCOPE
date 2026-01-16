#ifndef MESH_H
#define MESH_H

#include "SCOPE/vertex.h"
#include "SCOPE/shader.h"

#include "SCOPE/texture.h"
#include "SCOPE/VAO.h"
#include "SCOPE/VBO.h"
#include "SCOPE/EBO.h"

#include <vector>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
 
/**
 * @brief Class to create or import and transform a mesh
 */
class Mesh
{
    public : 
    std::vector<Vertex> vertices;   // vertices datas (vertices, UV, normals, colors)
    std::vector<Index> indices;     // indices to draw triangles
    std::vector<Texture> textures;  // 

    /**
     * @brief Construct a mesh from the vertex datas, the index datas, and the material and the assigned material
     * 
     * @param vertices_ vertex datas
     * @param indices_ index datas_
     * @param textures_ materials
     */
    Mesh(std::vector<Vertex> vertices_, std::vector<GLuint> indices_, std::vector<Texture> textures_);

    /**
     * @brief Draw the mesh
     * 
     * @param shader 
     */
    void draw(Shader& shader);

    /**
     * @brief Compute and return the model matrix
     * 
     * @return model matrix of the mesh
     */
    glm::mat4 getModelMatrix();

    /**
     * @brief Change the model matrix with an other model matrix
     * 
     * @param modelMatrix_ existing model matrix
     */
    void setModelMatrix(const glm::mat4& modelMatrix_);

    private : 
    
    VAO VAO;    // VAO
    glm::mat4 modelMatrix;  // model matrix

    /**
     * @brief Create an EBO and VBO and fill the VAO with vertex, UV, and normal datas
     */
    void setup();     
};

#endif
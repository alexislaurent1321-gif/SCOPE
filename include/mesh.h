#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vertex.h"
#include "shader.h"

#include "texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <iomanip>
#include <stdexcept>
#include <string>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
 
class Mesh{
    public : 
    std::vector<Vertex> vertices;
    std::vector<Index> indices;
    std::vector<Texture> textures;

    Mesh::Mesh(std::vector<Vertex> vertices_, std::vector<GLuint> indices_, std::vector<Texture> textures_);
    void draw(Shader& shader);
    glm::mat4 getModelMatrix();
    void setModelMatrix(const glm::mat4& modelMatrix_);

    private : 
    VAO VAO;
    glm::mat4 modelMatrix;

    void setup();     
};

#endif
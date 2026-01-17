

#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>

#include "SCOPE/model/mesh.h"
#include "SCOPE/shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

/**
 * @brief Class that load a gltf model with node processing and specular, diffuse texture and model transformation
 * 
 */
class Model {

private:
    Shader shader = Shader("resources/shaders/default_lights.vert", "resources/shaders/default_lights.frag");

    /**
     * @brief Load the model
     * 
     * @param path 
     */
    void load(std::string const &path);

    /**
     * @brief Process
     * 
     * @param node 
     * @param scene 
     * @param parentTransform 
     */
    void processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform = glm::mat4(1.f));
    
    /**
     * @brief 
     * 
     * @param mesh 
     * @param scene 
     * @return Mesh 
     */
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    /**
     * @brief 
     * 
     * @param mat 
     * @param type 
     * @param typeName 
     * @return std::vector<Texture> 
     */
    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
    
    /**
     * @brief Convert an assimp matrix to a glm matrix 
     * 
     * @param aiMat 
     * @return glm::mat4 
     */
    glm::mat4 Model::AiMat4ToGlm(const aiMatrix4x4* aiMat);

    // Transform
    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 scale{1.f};
    glm::vec3 orientation{0.f, 0.f, 0.f};
    glm::mat4 modelMatrix{1.f};

    /**
     * @brief Update the model matrix with new transform variables
     */
    void updateModelMatrix();


public:
    // Model data 
    std::vector<Texture> textures;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;

    // Constructors
    Model(std::string const &path);
    void draw();

    // Transform
    void setPosition(glm::vec3 position_);
    void setOrientation(glm::vec3 orientation_);
    void setScale(glm::vec3 scale_);

    void setShader(const Shader& shader_){shader = shader_;}
    
    /**
     * @brief Get the Model Matrix object
     * 
     * @return glm::mat4 
     */
    glm::mat4 getModelMatrix() const;

    Shader getShader() const{return shader;}
};

#endif


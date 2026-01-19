

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

namespace SCOPE {

/**
 * @brief Class to represent a 3D model composed of meshes, with methods to load and draw it
 * @details class taken partly from the tutorial LearnOpenGL
 * @see https://learnopengl.com/Getting-started/Shaders
 */
class Model {

private:

    /**
     * @brief Load a model from file
     * 
     * @param path 
     */
    void load(std::string const &path);

    /**
     * @brief 
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
     * @brief Load material textures
     * 
     * @param material 
     * @param type 
     * @param typeName 
     * @return std::vector<Texture> 
     */
    std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
    
    /**
     * @brief Convert an aiMatrix4x4 to glm::mat4
     * 
     * @param aiMat 
     * @return glm::mat4 
     */ 
    glm::mat4 Model::AiMat4ToGlm(const aiMatrix4x4* aiMat);

    // Transform
    glm::vec3 position{0.f, 0.f, 0.f};  ///< position of the model
    glm::vec3 scale{1.f};               ///< scale of the model
    glm::vec3 orientation{0.f, 0.f, 0.f};   ///< orientation of the model (in degrees)
    glm::mat4 modelMatrix{1.f};         ///< model matrix

    /**
     * @brief Update the model matrix from position, scale and orientation
     * 
     */
    void updateModelMatrix();


public:
    // Model data 
    std::vector<Texture> textures;	      ///< loaded textures to avoid loading duplicates
    std::vector<Mesh> meshes;       ///< meshes composing the model
    std::string directory;            ///< directory of the model file

    // Constructors
    
    /**
     * @brief Constructor by loading a model from file
     * 
     * @param path 
     */
    Model(std::string const &path); 

    /**
     * @brief Draw the model by drawing each mesh composing it
     * 
     * @param shader 
     */
    void draw(Shader& shader);

    // Transform
    void setPosition(glm::vec3 position_);
    void setOrientation(glm::vec3 orientation_);
    void setScale(glm::vec3 scale_);
    
    /**
     * @brief Get the model matrix of the model
     * 
     * @return glm::mat4 
     */
    glm::mat4 getModelMatrix() const;
};

}

#endif


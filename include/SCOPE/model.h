

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

#include "SCOPE/mesh.h"
#include "SCOPE/shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model {

private:
    void load(std::string const &path);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    void processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform = glm::mat4(1.f));
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    glm::mat4 Model::AiMat4ToGlm(const aiMatrix4x4* aiMat);

    // Transform
    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 scale{1.f};
    glm::vec3 orientation{0.f, 0.f, 0.f};
    glm::mat4 modelMatrix{1.f};
    void updateModelMatrix();


public:
    // Model data 
    std::vector<Texture> textures;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;

    // Constructors
    Model(std::string const &path);
    void draw(Shader &shader);

    // Transform
    void setPosition(glm::vec3 position_);
    void setOrientation(glm::vec3 orientation_);
    void setScale(glm::vec3 scale_);
    glm::mat4 getModelMatrix() const;
};

#endif




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

#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model {

private:

    // Transformations
    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 scale{1.f};
    glm::vec3 orientation{0.f, 0.f, 0.f};
    glm::mat4 modelMatrix{1.f};

    void load(std::string const &path);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    void processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform = glm::mat4(1.f));
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    glm::mat4 Model::AiMat4ToGlm(const aiMatrix4x4* from);


public:
    // model data 
    std::vector<Texture> textures;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;

    Model(std::string const &path);
    void draw(Shader &shader);

    void setPosition(glm::vec3 position_){
        position = position_;
        updateModelMatrix();
    }

    void setOrientation(glm::vec3 orientation_){
        orientation = orientation_;
        updateModelMatrix();
    }

    void setScale(glm::vec3 scale_){
        scale = scale_;
        updateModelMatrix();
    }

    void updateModelMatrix(){
        modelMatrix = glm::scale(glm::mat4(1.f), 0.1f * scale);
        modelMatrix = glm::rotate(modelMatrix, orientation.x, glm::vec3(1.f, 0.f, 0.f));
        modelMatrix = glm::rotate(modelMatrix, orientation.y, glm::vec3(0.f, 1.f, 0.f));
        modelMatrix = glm::rotate(modelMatrix, orientation.z, glm::vec3(0.f, 0.f, 1.f));
        modelMatrix = glm::translate(modelMatrix, position);
    }

    glm::mat4 getModelMatrix() const{
        return modelMatrix;
    }
    
};

#endif




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

class Model 
{
public:
    // model data 
    std::vector<Texture> textures;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;

    Model(std::string const &path);
    void draw(Shader &shader);

    // Transformations
    glm::vec3 position{0.f, 0.f, 1.f};
    glm::vec3 size{1.f};
    glm::vec3 orientation{0.f, 0.f, 0.f};

    glm::mat4 getModelMatrix() const{
        glm::mat4 model(1.f);
        model = glm::scale(model, 0.1f * size);
        model = glm::rotate(model, orientation.x, glm::vec3(1.f, 0.f, 0.f));
        model = glm::rotate(model, orientation.y, glm::vec3(0.f, 1.f, 0.f));
        model = glm::rotate(model, orientation.z, glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, position);
        return model;
    }
    
private:
    void load(std::string const &path);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    void processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform = glm::mat4(1.f));
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    glm::mat4 Model::AiMat4ToGlm(const aiMatrix4x4* from);

    
};

#endif


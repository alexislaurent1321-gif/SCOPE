#include "model.h"

Model::Model(std::string const &path){
    load(path);
}

void Model::draw(Shader &shader){
    for(Mesh& mesh : meshes){
        shader.setUniform("model", getModelMatrix() * mesh.getModelMatrix());
        mesh.draw(shader);
    }
}

// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void Model::load(std::string const &path){
    // read file via ASSIMP
    Assimp::Importer importer;
    importer.SetPropertyBool(AI_CONFIG_IMPORT_NO_SKELETON_MESHES, true);
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    updateModelMatrix();
    processNode(scene->mRootNode, scene, this->getModelMatrix());
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform)
{
    glm::mat4 transform = AiMat4ToGlm(&node -> mTransformation);
    glm::mat4 globalTransformation = parentTransform * transform;

    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

		Mesh mesh = processMesh(assimpMesh, scene);
		mesh.setModelMatrix(globalTransformation);
		meshes.push_back(mesh);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, globalTransformation);
}

glm::mat4 Model::AiMat4ToGlm(const aiMatrix4x4* aiMat){
	glm::mat4 mat;
	mat[0][0] = (GLfloat)aiMat->a1; mat[0][1] = (GLfloat)aiMat->b1;  mat[0][2] = (GLfloat)aiMat->c1; mat[0][3] = (GLfloat)aiMat->d1;
	mat[1][0] = (GLfloat)aiMat->a2; mat[1][1] = (GLfloat)aiMat->b2;  mat[1][2] = (GLfloat)aiMat->c2; mat[1][3] = (GLfloat)aiMat->d2;
	mat[2][0] = (GLfloat)aiMat->a3; mat[2][1] = (GLfloat)aiMat->b3;  mat[2][2] = (GLfloat)aiMat->c3; mat[2][3] = (GLfloat)aiMat->d3;
	mat[3][0] = (GLfloat)aiMat->a4; mat[3][1] = (GLfloat)aiMat->b4;  mat[3][2] = (GLfloat)aiMat->c4; mat[3][3] = (GLfloat)aiMat->d4;

	return mat;
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) 
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.UV = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.UV = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures_tab;
    for(unsigned int unit = 0; unit < material->GetTextureCount(type); unit++)
    {
        aiString str;
        material->GetTexture(type, unit, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures.size(); j++)
        {
            if(std::strcmp(textures[j].path.data(), str.C_Str()) == 0)
            {
                textures_tab.push_back(textures[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   
            // if texture hasn't been loaded already, load it
            Texture texture(str.C_Str(), this->directory, unit);
            texture.type = typeName;
            textures.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
            textures_tab.push_back(texture);
        }
    }
    return textures;
}


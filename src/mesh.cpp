#include "SCOPE/mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices_, std::vector<GLuint> indices_, std::vector<Texture> textures_) : 
    vertices(vertices_),
    indices(indices_),
	textures(textures_)
{
    setup();
}

void Mesh::setup(){
	
    VAO.bind();
    VBO VBO(vertices);
    EBO EBO(indices);
 
    VAO.linkVBO(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.linkVBO(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	VAO.linkVBO(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, UV));
    
    VAO.unbind();
	VBO.unbind();
	EBO.unbind();
}  

void Mesh::draw(Shader &shader){
    unsigned int diffuseNum = 1;
    unsigned int specularNum = 1;
    unsigned int normalNum = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string number;
		std::string name = textures[i].type;
		if (name == "diffuse")
			number = std::to_string(diffuseNum++);
		else if (name == "specular")
			number = std::to_string(specularNum++);
		else if (name == "normal")
			number = std::to_string(normalNum++);

		shader.setUniform(("material." + name + number).c_str(), i);
		textures[i].bind(i);
	}
    VAO.bind();

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    VAO.unbind();
}

glm::mat4 Mesh::getModelMatrix(){
	return modelMatrix;
}

void Mesh::setModelMatrix(const glm::mat4& modelMatrix_){
	modelMatrix = modelMatrix_;
}
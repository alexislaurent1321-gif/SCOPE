#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include "vertex.h"

/**
 * @brief Little class to create and manage a VBO
 */
class VBO
{
public:

	GLuint ID;  // identifier of a VBO

	/**
     * @brief VBO contructed by giving the vertex datas of a mesh
     */
	VBO(std::vector<Vertex> vertices);

	/**
     * @brief Bind the VBO by initializing the identifier, create the buffer and assigning the storage space for the vertex datas
     */
	void bind();

	/**
     * @brief Unbind the VBO by assigning 0 to the identifier
     */
	void unbind();

	/**
	 * @brief Delete the VBO
	 */
	void deleteBuffer();
};

inline VBO::VBO(std::vector<Vertex> vertices){
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

inline void VBO::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

inline void VBO::unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void VBO::deleteBuffer(){
	glDeleteBuffers(1, &ID);
}

#endif
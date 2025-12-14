#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>
#include "vertex.h"


class VBO
{
public:

	GLuint ID;

	VBO(std::vector<Vertex> vertices);

	void bind();
	void unbind();

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
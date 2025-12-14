#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:

	GLuint ID;

	VAO();

	void linkVBO(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    
	void bind();
	void unbind();

	void deleteArray();
};

inline VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

inline void VAO::linkVBO(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
    VBO.bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

inline void VAO::bind(){
    glBindVertexArray(ID);
}

inline void VAO::unbind(){
    glBindVertexArray(0);
}

inline void VAO::deleteArray(){
    glDeleteVertexArrays(1, &ID);
}

#endif

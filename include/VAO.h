#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

/**
 * @brief Little class to create and manage a VAO
 */
class VAO
{
public:

	GLuint ID;  // identifier of a VAO

    /**
     * @brief Default constructor
     */
	VAO();

    /**
     * @brief Fill the VAO from the vertex datas
     */
	void linkVBO(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    
    /**
     * @brief Bind the VAO
     */
	void bind();

    /**
     * @brief Unbind the VAO by assigning 0 to the identifier
     */
	void unbind();

    /**
     * @brief Delete the VAO
     */
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

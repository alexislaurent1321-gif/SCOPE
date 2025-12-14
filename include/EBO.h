#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

typedef GLuint Index;

class EBO
{
public:
	GLuint ID;

    EBO(std::vector<Index> indices);

    void bind();
    void unbind();

    void deleteElement();
};

inline EBO::EBO(std::vector<Index> indices){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index), indices.data(), GL_STATIC_DRAW);
}

inline void EBO::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

inline void EBO::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline void EBO::deleteElement(){
    glDeleteBuffers(1, &ID);
}

#endif

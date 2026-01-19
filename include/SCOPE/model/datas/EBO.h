#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

typedef GLuint Index; // the indices are of type integer

namespace SCOPE {

/**
 * @brief Little class to create and manage an EBO
 */
class EBO
{
public:
	GLuint ID;  ///< identifier of an EBO

    /**
     * @brief EBO contructed by giving the indices of a mesh
     */
    EBO(std::vector<Index> indices);

    /**
     * @brief Bind the EBO by initializing the identifier, create the buffer and assigning the storage space for the index datas
     */
    void bind();

    /**
     * @brief Unbind the EBO by assigning 0 to the identifier
     */
    void unbind();

    /**
     * @brief Delete the buffer
     */
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

}

#endif

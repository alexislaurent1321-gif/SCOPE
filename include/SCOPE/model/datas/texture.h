#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>
#include <iostream>


class Texture {

public:
    GLuint ID;
    std::string type;
    std::string path;

    /**
     * @brief Default constructor of a Texture object
     * 
     */
    Texture();

    /**
     * @brief Constructor by given attributes
     * 
     * @param path_ 
     * @param directory 
     * @param unit 
     */
    Texture(std::string path_, std::string directory, GLuint unit);

    /**
     * @brief Load a texture
     * 
     * @param path_ 
     * @param directory 
     * @param unit 
     */
    void load(std::string path_, std::string directory, GLuint unit);
    void bind(GLuint unit) const;
    void unbind() const;
};
#endif




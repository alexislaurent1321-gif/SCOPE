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

    Texture();
    Texture(std::string path_, std::string directory, GLuint unit);

    void load(std::string path_, std::string directory, GLuint unit);
    void bind(GLuint unit) const;
    void unbind() const;
};
#endif




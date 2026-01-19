#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>
#include <iostream>

namespace SCOPE {

class Texture {

public:
    GLuint ID;            ///< identifier of the texture
    std::string type;           ///< type of the texture (diffuse, specular, normal, height)
    std::string path;        ///< path of the texture file

    /**
     * @brief Default constructor
     * 
     */
    Texture();

    /**
     * @brief Constructor by giving the path, the directory and the unit of the texture
     * 
     * @param path_ 
     * @param directory 
     * @param unit 
     */
    Texture(std::string path_, std::string directory, GLuint unit);

    /**
     * @brief Load the texture from a file
     * 
     * @param path_ 
     * @param directory 
     * @param unit 
     */
    void load(std::string path_, std::string directory, GLuint unit);
    
    /**
     * @brief Bind the texture to a texture unit
     * 
     * @param unit 
     */
    void bind(GLuint unit) const;
    
    /**
     * @brief Unbind the texture
     * 
     */
    void unbind() const;
};

}

#endif




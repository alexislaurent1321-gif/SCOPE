

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace SCOPE {

/**
 * @brief Class to manage a shader program
 * @details shader class and default shaders taken partly from the tutorial LearnOpenGL
 * @see https://learnopengl.com/Getting-started/Shaders
 */
class Shader
{
public:
    unsigned int ID;

    /**
     * @brief Constructor by giving the path of the vertex shader and the fragment shader
     * 
     * @param vertexPath 
     * @param fragmentPath 
     */
    Shader(const char* vertexPath, const char* fragmentPath);

    /**
     * @brief Load a vertex shader and a fragment shader by given pathes
     * 
     * @param vertexPath 
     * @param fragmentPath 
     */
    void load(const char* vertexPath, const char* fragmentPath);

    /**
     * @brief Use/activate the shader
     * 
     */
    void use() const;

    /**
     * @brief Passing a variable to the shader (polymorphism for each type)
     * 
     * @param name 
     * @param value 
     */
    void setUniform(const std::string &name, bool value) const;
    void setUniform(const std::string &name, int value) const;
    void setUniform(const std::string &name, unsigned int value) const;
    void setUniform(const std::string &name, float value) const;
    void setUniform(const std::string &name, const glm::vec2 &value) const;
    void setUniform(const std::string &name, float x, float y) const;
    void setUniform(const std::string &name, const glm::vec3 &value) const;
    void setUniform(const std::string &name, float x, float y, float z) const;
    void setUniform(const std::string &name, const glm::vec4 &value) const;
    void setUniform(const std::string &name, float x, float y, float z, float w) const;
    void setUniform(const std::string &name, const glm::mat2 &mat) const;
    void setUniform(const std::string &name, const glm::mat3 &mat) const;
    void setUniform(const std::string &name, const glm::mat4 &mat) const;

private:
    /**
     * @brief Check compilation errors of the shader
     * 
     * @param shader 
     * @param type 
     */
    void checkCompileErrors(GLuint shader, std::string type);
};

}

#endif


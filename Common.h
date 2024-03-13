#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct Vertex {
    float x, y, z; // Position
    float r, g, b; // Color
};

class Shader {
public:
    unsigned int ID;
    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // Use the shader
    void use();
    // Utility functions for setting uniforms
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    // Add other methods as needed...

private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif // COMMON_H

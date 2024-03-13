#ifndef GROUND_H
#define GROUND_H

#include "Common.h"

class Ground {
public:
    std::vector<Vertex> vertices;
    glm::mat4 matrix;
    unsigned int VAO, VBO;

    Ground();
    void setupMesh();
    void Draw(Shader& shader);
};

#endif // GROUND_H

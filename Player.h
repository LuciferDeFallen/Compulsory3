#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"

class Player {
public:
    std::vector<Vertex> vertices;
    glm::mat4 matrix;
    unsigned int VAO, VBO;
    float positionX = -1.0f;
    float positionY = 1.0f;
    float velocityY;

    float sizeY = 0.2f;
    float sizeX = 0.1f;

    Player();
    void setupMesh();
    void Jump();
    void Tick();
    void Draw(Shader& shader);
    void Move(float deltaX); // Method to update player's horizontal position
};

#endif // PLAYER_H

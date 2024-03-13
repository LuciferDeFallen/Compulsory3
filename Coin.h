#ifndef COIN_H
#define COIN_H

#include "Common.h"
#include "Player.h"

class Coin {
public:
    std::vector<Vertex> vertices;
    glm::mat4 matrix;
    unsigned int VAO, VBO;

    bool collected = false;

    float positionX;
    float positionY;

    float sizeY = 0.1f;
    float sizeX = 0.1f;

    Coin(float positionX, float positionY);
    void setupMesh();
    void Collides(Player& player);
    void Draw(Shader& shader);
};



#endif // COIN_H

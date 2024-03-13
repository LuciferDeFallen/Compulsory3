#ifndef DOOR_H
#define DOOR_H

#include "Common.h"
#include "Player.h"

class Door {
public:
    std::vector<Vertex> vertices;
    glm::mat4 matrix;
    unsigned int VAO, VBO;

    bool collected = false;

    float positionX;
    float positionY;

    float sizeY = 0.3f;
    float sizeX = 0.2f;

    Door(float positionX, float positionY);
    void setupMesh();
    bool Collides(Player& player);
    void Draw(Shader& shader);
};



#endif // DOOR_H

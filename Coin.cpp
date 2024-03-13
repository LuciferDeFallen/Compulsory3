#include "Coin.h"
#include "PLayer.h"
#include <glm/gtc/matrix_transform.hpp>

Coin::Coin(float positionX, float positionY) : 
    positionY(positionY), positionX(positionX) {
    this->setupMesh();
}

void Coin::setupMesh() {
    // Define vertices for a square (two triangles)
    float size = 0.025f; // Half the side length of the square
    
    vertices = {
        {0.0f, sizeY, 0.0f,    1.0f, 0.0f, 0.0f}, // Top left
        {sizeX, sizeY, 0.0f,     1.0f, 0.0f, 0.0f}, // Top right
        {0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f}, // Bottom left

        {sizeX, sizeY, 0.0f,     1.0f, 0.0f, 0.0f}, // Top right
        {sizeX, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f}, // Bottom right
        {0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f}  // Bottom left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Coin::Collides(Player& player) {
    // Check if player's and coin's rectangles overlap
    bool collisionX = player.positionX + player.sizeX >= positionX &&
        positionX + sizeX >= player.positionX;
    bool collisionY = player.positionY + player.sizeY >= positionY &&
        positionY + sizeY >= player.positionY;

    if (collisionX&& collisionY) collected = true;
}

void Coin::Draw(Shader& shader) {
    if (collected) return;
    shader.use();

    glm::mat4 model = glm::mat4(1.0f); // Start with the identity matrix
    model = glm::translate(model, glm::vec3(positionX, -.5 + positionY, 0.0f)); // Apply translation based on positionX and fixed Y

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size()));
    glBindVertexArray(0);
}

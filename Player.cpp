#include "Player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Player::Player() {
    this->setupMesh();
}

void Player::setupMesh() {
    // Player as a small rectangle (0.1 width, 0.15 height)
    float height = 0.075f;
    /*vertices = {
        // Positions               // Colors (will be overridden by fragment shader)
        {-0.05f, height, 0.0f,    1.0f, 0.0f, 0.0f}, // Top left
        {0.05f, height, 0.0f,     1.0f, 0.0f, 0.0f}, // Top right
        {-0.05f, -height, 0.0f,   1.0f, 0.0f, 0.0f}, // Bottom left

        {0.05f, height, 0.0f,     1.0f, 0.0f, 0.0f}, // Top right
        {0.05f, -height, 0.0f,    1.0f, 0.0f, 0.0f}, // Bottom right
        {-0.05f, -height, 0.0f,   1.0f, 0.0f, 0.0f}  // Bottom left
    };*/
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // Unbind VAO
}

void Player::Jump() {
    if (positionY <= 0) {
        velocityY = 0.07f;
    }
}

void Player::Tick() {
    if (positionY > 0) velocityY -= 0.004f;
    positionY += velocityY;
    if (positionY < 0) positionY = 0;
}

void Player::Move(float deltaX) {
    positionX += deltaX; // Update position based on input
    // Ensure the player remains within the window bounds
    if (positionX > 1.0f) positionX = -1.1f;
    if (positionX < -1.1f) positionX = 1.0f;
}

void Player::Draw(Shader& shader) {
    float height = 0.075f;
    shader.use();

    glm::mat4 model = glm::mat4(1.0f); // Start with the identity matrix
    model = glm::translate(model, glm::vec3(positionX, -.5 + positionY, 0.0f)); // Apply translation based on positionX and fixed Y

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size()));
    glBindVertexArray(0);
}


#include "Ground.h"

Ground::Ground() {
    this->setupMesh();
}

void Ground::setupMesh() {
    // Define vertices for two triangles that form a rectangle covering the bottom half of the screen
    vertices = {
        // Positions            // Colors (will be overridden by fragment shader)
        {-1.0f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f},  // Bottom left
        {1.0f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f},  // Bottom right
        {-1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f},  // Top left

        {1.0f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f},  // Bottom right
        {1.0f, -1.0f, 0.0f,    0.0f, 1.0f, 0.0f},  // Top right
        {-1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f}   // Top left
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

void Ground::Draw(Shader& shader) {
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6); // Draw 6 vertices forming two triangles
    glBindVertexArray(0);
}

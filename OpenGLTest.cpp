#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Common.h"
#include "Player.h"
#include "Door.h"
#include "Ground.h"
#include "Coin.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

/*
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
*/

int S_DOWN;
int room = 0;
void processInput(GLFWwindow* window, Player& player) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player.Move(-0.015f); // Move left
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player.Move(0.015f); // Move right
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player.Jump(); // Move right
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        S_DOWN = S_DOWN + 1;
    }
    else S_DOWN = 0;
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Scene", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    Shader ourShader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    Shader playerShader("shaders/player.vert", "shaders/red.frag");
    Shader groundShader("shaders/vertexShader.vert", "shaders/green.frag");
    Shader floorShader("shaders/vertexShader.vert", "shaders/gray.frag");
    Shader coinShader("shaders/player.vert", "shaders/yellow.frag");
    Shader doorShader("shaders/player.vert", "shaders/brown.frag");
    Player player;
    Ground ground;
    Door door1 = Door(0.75, 0.0f);
    Door door2 = Door(0.75, 0);
    player.setupMesh();

    // Placing coins!!
    std::vector<Coin> coins;
    coins.emplace_back(Coin(-0.7f, 0.05f)); // Example position
    coins.emplace_back(Coin(0.4f, 0.5f)); // Example position
    coins.emplace_back(Coin(0.8f, 0.5f)); // Example position
    coins.emplace_back(Coin(0.6f, 0.6f)); // Example position
    for (auto& coin : coins) {
        coin.setupMesh();
    }


    while (!glfwWindowShouldClose(window)) {
        processInput(window, player);
        player.Tick();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        door1.Draw(doorShader);
        std::cout << S_DOWN;
        if (room == 0) {
            // Transformations and drawing code here
            ground.Draw(groundShader);
            for (auto& coin : coins) {
                coin.Collides(player);
                coin.Draw(coinShader);
            }
            if (door1.Collides(player) and S_DOWN==1) {
                room = 1;
            }
        }
        else if (room == 1) {
            ground.Draw(floorShader);
            if (door1.Collides(player) and S_DOWN==1) {
                room = 0;
            }
        }
        player.Draw(playerShader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }    

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

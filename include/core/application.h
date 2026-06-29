#ifndef APPLICATION_H
#define APPLICATION_H
#include "shader.h"
#include "camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#pragma once
class Application{
public:
    Application(int width, int height, const char* title);
    ~Application();
    virtual void onUpdate(float deltaTime) = 0;
    virtual void onRender(const glm::mat4& view, const glm::mat4& projection) = 0;
    void run();
 
    Camera camera = Camera(glm::vec3(3.0f, 4.0f, 8.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f),
                  -90.0f, -45.0f);
    Shader* ourShader = nullptr;
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void processInput(GLFWwindow *window);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    GLFWwindow* window;
    bool firstMouse = true;
    float lastX = 400, lastY = 300;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO, EBO;
};

#endif

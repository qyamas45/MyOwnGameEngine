#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#pragma once
class Window{
public:
    Window(int width, int height, const char* title);
    ~Window();
    virtual void onUpdate(float deltaTime) = 0;
    virtual void onRender() = 0;
    void run();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void processInput(GLFWwindow *window);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    GLFWwindow* window;
    bool firstMouse = true;
    float lastX = 400, lastY = 300;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO, EBO;
};

#endif

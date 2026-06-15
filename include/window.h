#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Window{
public:
    Window(int width, int height, const char* title);
    ~Window();
    void swapBuffers();
    bool shouldClose();
    void pollEvents();
    void run();
private:
    GLFWwindow* window;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    unsigned int VBO, VAO, EBO;
};

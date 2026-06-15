#include <iostream>
#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



 
int main() {
    Window window(800, 600, "Game Engine");
    window.run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

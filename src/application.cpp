#include "application.h"
#include <direct.h>  // Windows only
Application::Application(int width, int height, const char* title){
    
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
        return;
    }
     
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    //input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    
        throw std::runtime_error("Failed to initialize GLAD");
    } 
    glEnable(GL_DEPTH_TEST);
    ourShader = new Shader("shaders/camera.vs", "shaders/camera.fs");

}

Application::~Application(){

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();

}
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void Application::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    // Implement mouse movement handling here
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if(self->firstMouse)
    {
        self->lastX = xpos;
        self->lastY = ypos;
        self->firstMouse = false;
    }
    float xoffset = xpos - self->lastX;
    float yoffset = self->lastY - ypos; // reversed since y-coordinates go from bottom
    self->lastX = xpos;
    self->lastY = ypos;
    self->camera.ProcessMouseMovement(xoffset, yoffset);

}
void Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    self->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void Application::processInput(GLFWwindow *window)
{ 
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    // Implement input processing here
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // Camera movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        self->camera.ProcessKeyboard(FORWARD, self->deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        self->camera.ProcessKeyboard(BACKWARD, self->deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        self->camera.ProcessKeyboard(LEFT, self->deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        self->camera.ProcessKeyboard(RIGHT, self->deltaTime);


}

//function should run the program
void Application::run()
{
    float lastFrame = 0.0f;
    while(!glfwWindowShouldClose(this->window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        processInput(this->window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ourShader->use();
        glm::mat4 projection = glm::perspective(glm::radians(this->camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader->setMat4("projection", projection);
        
        glm::mat4 view = this->camera.GetViewMatrix();
        ourShader->setMat4("view", view);

        onUpdate(this->deltaTime);
        onRender(view, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout << "Exiting run loop" << std::endl;
}

#include "ball.h"


Ball::Ball(float x, float y, float z, float radius) : x(x), y(y), 
z(z), radius(radius), 
shader(Shader("shaders/ball.vs", "shaders/ball.fs")) {
    position = glm::vec3(x, y, z);
    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    scale = glm::vec3(1.0f);
    color = glm::vec3(1.0f, 0.0f, 0.0f); // Red color

    setupMesh();
}
Ball::~Ball() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Ball::setupMesh() {

    const int segments = 36;
    const float M_PI = 3.14159265358979323846f;
    float vertices[segments * 3];
    for (int i = 0; i < segments; ++i) {
        float angle = i * 2.0f * M_PI / segments;
        vertices[i * 3] = radius * cos(angle);
        vertices[i * 3 + 1] = radius * sin(angle);
        vertices[i * 3 + 2] = 0.0f;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Ball::update(float deltaTime) {
    // Update ball position or state if needed
}
void Ball::render() {
 
    // Render the ball using OpenGL
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    shader.setMat4("model", model);
    glm::mat4 projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f);
    shader.setMat4("projection", projection);

    shader.setVec3("color", color);  // sends the red color
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
    glBindVertexArray(0);
}

void Ball::draw(Shader& shader, glm::mat4 view, glm::mat4 projection) {
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 36);
    glBindVertexArray(0);
}
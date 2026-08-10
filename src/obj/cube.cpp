#include "objs/cube.h"


Cube::Cube(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, glm::vec3 color, float rotationAngle, bool useCustomColor)
    : scale(scale), rotationAxis(rotationAxis), color(color), rotationAngle(rotationAngle), useCustomColor(useCustomColor) {
    // Entity's members, set here rather than in the init list (they belong
    // to the base and are already constructed by this point).
    this->position = position;
    this->shader   = &ownShader;

    setupMesh();
}
void Cube::setupMesh()
{
    //Create a cube with vertices and indices
    float halfScaleX = scale.x / 2.0f;
    float halfScaleY = scale.y / 2.0f;
    float halfScaleZ = scale.z / 2.0f;
    vertices = {
        // positions          
        -halfScaleX, -halfScaleY, -halfScaleZ,
         halfScaleX, -halfScaleY, -halfScaleZ,
         halfScaleX,  halfScaleY, -halfScaleZ,
        -halfScaleX,  halfScaleY, -halfScaleZ,
        -halfScaleX, -halfScaleY,  halfScaleZ,
         halfScaleX, -halfScaleY,  halfScaleZ,
         halfScaleX,  halfScaleY,  halfScaleZ,
        -halfScaleX,  halfScaleY,  halfScaleZ
    };
    // 12 triangles, 2 per face. Wound counter-clockwise as seen from outside
    // the cube, which is OpenGL's default front-facing orientation.
    indices = {
        0, 2, 1,   0, 3, 2,   // back   (-z)
        4, 5, 6,   4, 6, 7,   // front  (+z)
        0, 4, 7,   0, 7, 3,   // left   (-x)
        1, 2, 6,   1, 6, 5,   // right  (+x)
        0, 1, 5,   0, 5, 4,   // bottom (-y)
        3, 7, 6,   3, 6, 2    // top    (+y)
    };

    // Generate and bind VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}
Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::clearArrays()
{
    std::vector<float>().swap(vertices);
    std::vector<unsigned int>().swap(indices);
}
void Cube::update(float)
{
    // static for now
}
void Cube::updateCollider()
{
    // no collider yet
}
void Cube::onCollision(Collider*, const float&)
{
    // no collider yet, so this is never reached
}
void Cube::setColor(glm::vec3 color)
{
    this->color = color;
    // An explicit color overrides the default white in render().
    useCustomColor = true;
}
void Cube::debug()
{
    std::cout << glm::to_string(position) << std::endl;
}

void Cube::render(const glm::mat4& view, const glm::mat4& projection) {
    shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    if (useCustomColor) {
        shader->setVec3("color", color);
    } else {
        shader->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f)); // Default color
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
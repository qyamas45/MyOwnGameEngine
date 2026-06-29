#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "shader.h"
#include <shader.h>
class Ball : public Entity {
public:
    Ball(float x, float y, float z, float radius);
    ~Ball();
    void draw(Shader&, glm::mat4, glm::mat4);
    void update(float deltaTime) override;
    void render(const glm::mat4& view, const glm::mat4& projection) override;
private:
    unsigned int VAO, VBO;
    float x, y, z, radius;
    glm::vec3 position;
    glm::vec3 rotationAxis;
    glm::vec3 scale;
    glm::vec3 color;
    Shader shader;
    void setupMesh();
};

#endif

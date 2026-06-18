#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "shader.h"

class Ball : public Entity {
public:
    Ball(float x, float y, float z, float radius);
    ~Ball();
    void draw(Shader&, glm::mat4, glm::mat4);
    void update(float deltaTime) override;
    void render() override;
private:
    unsigned int VAO, VBO;
    float x, y, z, radius;
    //Shader shader;
    void setupMesh();
};

#endif

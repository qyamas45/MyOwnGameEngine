#ifndef ENTITY_H
#define ENTITY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <iostream>
#include <GLFW/glfw3.h>

class Entity {
public:
    Entity() {}
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(const glm::mat4& view, const glm::mat4& projection) = 0;
};

#endif
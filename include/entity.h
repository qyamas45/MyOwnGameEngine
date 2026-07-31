#ifndef ENTITY_H
#define ENTITY_H
#define GLM_ENABLE_EXPERIMENTAL 
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <shader.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "collider.h"
 
class Entity {
public:
    Entity() {}
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void updateCollider() = 0;
    virtual Collider* getCollider() = 0;
    virtual void onCollision(Collider* other, const float& dt) = 0;
    virtual void render(const glm::mat4& view, const glm::mat4& projection) = 0;
    virtual void debug() = 0;
private:
    glm::vec3 position;
};

#endif
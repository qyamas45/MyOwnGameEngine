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

//This is a class that represents an entity in the game world. 
//It is an abstract class that defines the interface for all entities. 
//All entities must implement the update, updateCollider, getCollider, onCollision, 
//render, and debug methods. The Entity class also has a position and a collider. The position is a glm::vec3 that represents the position of the entity in the world. The collider is a pointer to a Collider object that represents the collision shape of the entity.
class Entity {
public:
    Entity() {}
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void updateCollider() = 0;
    virtual Collider* getCollider() = 0;
    virtual glm::vec3 getPosition() const  {return position;}
    virtual void setTexture(Shader* shader) {this->shader = shader;}
    virtual void setPosition(const glm::vec3& pos) {position = pos; updateCollider();}
    virtual void setAnchor(bool anchor) {this->anchor = anchor;}

    virtual void onCollision(Collider* other, const float& dt) = 0;
    virtual void render(const glm::mat4& view, const glm::mat4& projection) = 0;
    virtual void debug() = 0;
protected:
    // Shared entity state. Subclasses use these directly instead of
    // declaring their own copies, which would shadow these and leave
    // getPosition()/setPosition()/setTexture() operating on dead members.
    Shader* shader = nullptr;
    glm::vec3 position{0.0f};
    Collider* collider = nullptr;
    bool anchor = false;
};

#endif
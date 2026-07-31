#ifndef COLLIDER_H
#define COLLIDER_H
#include <glm/glm.hpp>
#include <iostream>
#include <memory>

class Collider {
public:
    enum class colliderTypes
    {
        CUBE = 0,
        SPHERE
    };
    Collider(colliderTypes t):colliderType(t){};
    virtual ~Collider() = default;

    virtual bool objectCollision(Collider* other) = 0;

    //getters
    colliderTypes getColliderType() const{
        return colliderType;
    }
    Collider* get()
    {
        return this;
    }
private:
colliderTypes colliderType;
};
#endif 
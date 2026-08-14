#ifndef CUBECOLLIDER_H
#define CUBECOLLIDER_H
#include "collider.h"
#include "collisionDetection.h"

class cubeCollider : public Collider{
public:
    cubeCollider(glm::vec3 center, glm::vec3 halfExtents) : 
    Collider(colliderTypes::CUBE), position(center), halfExtents(halfExtents) {};
    ~cubeCollider() override = default;
    cubeCollider* get() override { return this; }
    bool objectCollision(Collider* other) override;
    
    glm::vec3 getMinCoordinates();
    glm::vec3 getMaxCoordinates();
    
    glm::vec3 position;
    glm::vec3 halfExtents;
};
#endif
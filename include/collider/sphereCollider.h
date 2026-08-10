#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H
#include "collider.h"
#include "collisionDetection.h"
 
class sphereCollider : public Collider{
public:
    sphereCollider(glm::vec3 center, float radius) : 
    Collider(colliderTypes::SPHERE), position(center), radius(radius) {};
    ~sphereCollider() override = default;
    sphereCollider* get() override { return this; }
    
    bool objectCollision(Collider* other) override;
    glm::vec3 position;
    float radius;
};
#endif
#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <memory>
#include "collider.h"
#include "collider/sphereCollider.h"
class Collider;
class sphereCollider;

namespace collisionDetection
{
    bool SphereSphereIntersection(sphereCollider* s0, sphereCollider* s1);
};


#endif
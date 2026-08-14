#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <memory>
#include "collider.h"
#include "collider/sphereCollider.h"
#include "collider/cubeCollider.h"
#include <algorithm>

class Collider;
class sphereCollider;
class cubeCollider;
namespace collisionDetection
{
    bool SphereSphereIntersection(sphereCollider* s0, sphereCollider* s1);
    bool SphereCubeIntersection(sphereCollider* s, cubeCollider* c);
    bool CubeCubeIntersection(cubeCollider* c0, cubeCollider* c1);
};


#endif
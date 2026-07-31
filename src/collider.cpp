#include "collider.h"
#include "collider/sphereCollider.h"
#include "collisionDetection.h"

bool sphereCollider::objectCollision(Collider* other)
{
    switch(other->getColliderType())
    {
        case Collider::colliderTypes::SPHERE:
            return collisionDetection::SphereSphereIntersection(this, dynamic_cast<sphereCollider*>(other));
        default:
            return false;
    }
}

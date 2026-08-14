#include "collider.h"
#include "collider/sphereCollider.h"
#include "collider/cubeCollider.h"
#include "collisionDetection.h"

bool sphereCollider::objectCollision(Collider* other)
{
    switch(other->getColliderType())
    {
        case Collider::colliderTypes::SPHERE:
            return collisionDetection::SphereSphereIntersection(this, dynamic_cast<sphereCollider*>(other));
        case Collider::colliderTypes::CUBE:
            return collisionDetection::SphereCubeIntersection(this, dynamic_cast<cubeCollider*>(other));
        default:
            return false;
    }
}
bool cubeCollider::objectCollision(Collider* other)
{
    switch(other->getColliderType())
    {
        case Collider::colliderTypes::CUBE:
            return collisionDetection::CubeCubeIntersection(this, dynamic_cast<cubeCollider*>(other));
        case Collider::colliderTypes::SPHERE:
            return collisionDetection::SphereCubeIntersection(dynamic_cast<sphereCollider*>(other), this);
        default:
            return false;
    }
}
glm::vec3 cubeCollider::getMinCoordinates()
{
    return position - halfExtents;
}
glm::vec3 cubeCollider::getMaxCoordinates()
{
    return position + halfExtents;
}

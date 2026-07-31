#include "collisionDetection.h"
 
bool collisionDetection::SphereSphereIntersection(sphereCollider* s0, sphereCollider* s1)
{
    const glm::vec3& center0 = s0->position;
    const glm::vec3& center1 = s1->position;

    const float& r0 = s0->radius;
    const float& r1 = s1->radius;

    const float dist2 = glm::dot(center0 - center1, center0 - center1);
    const float rSum = r0 + r1;
    return dist2 <= (rSum*rSum);

}
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
bool collisionDetection::CubeCubeIntersection(cubeCollider* c0, cubeCollider* c1)
{
    //A cube (or rectangular cuboid) is defined by its minimum coordinates 
    //\((X_{min}, Y_{min}, Z_{min})\) and maximum coordinates 
    //\((X_{max}, Y_{max}, Z_{max})\), or by a center point 
    //\((C_x, C_y, C_z)\) and half-extents \((H_x, H_y, H_z)\) 
    //where \(X_{max} = C_x + H_x\) and \(X_{min} = C_x - H_x\)
    
    const glm::vec3& min0 = c0->getMinCoordinates();
    const glm::vec3& max0 = c0->getMaxCoordinates();

    const glm::vec3& min1 = c1->getMinCoordinates();
    const glm::vec3& max1 = c1->getMaxCoordinates();

    if (max0.x < min1.x || min0.x > max1.x) return false; // No overlap in x-axis
    if (max0.y < min1.y || min0.y > max1.y) return false; // No overlap in y-axis
    if (max0.z < min1.z || min0.z > max1.z) return false; // No overlap in z-axis

    return true;


    // Implement cube-cube intersection logic here
    return false; // Placeholder
}
bool collisionDetection::CubeSphereIntersection(cubeCollider* c, sphereCollider* s)
{
    // Get the sphere's center and radius
    const glm::vec3& sphereCenter = s->position;
    const float& sphereRadius = s->radius;

    // Get the cube's min and max coordinates
    const glm::vec3& cubeMin = c->getMinCoordinates();
    const glm::vec3& cubeMax = c->getMaxCoordinates();

    // Find the closest point on the cube to the sphere's center
    glm::vec3 closestPoint;
    closestPoint.x = std::max(cubeMin.x, std::min(sphereCenter.x, cubeMax.x));
    closestPoint.y = std::max(cubeMin.y, std::min(sphereCenter.y, cubeMax.y));
    closestPoint.z = std::max(cubeMin.z, std::min(sphereCenter.z, cubeMax.z));

    // Calculate the distance from the sphere's center to the closest point
    float distanceSquared = glm::dot(closestPoint - sphereCenter, closestPoint - sphereCenter);

    // Check if the distance is less than or equal to the square of the radius
    return distanceSquared <= (sphereRadius * sphereRadius);
}
bool collisionDetection::SphereCubeIntersection(sphereCollider* s, cubeCollider* c)
{
    // Get the sphere's center and radius
    const glm::vec3& sphereCenter = s->position;
    const float& sphereRadius = s->radius;

    // Get the cube's min and max coordinates
    const glm::vec3& cubeMin = c->getMinCoordinates();
    const glm::vec3& cubeMax = c->getMaxCoordinates();

    // Find the closest point on the cube to the sphere's center
    glm::vec3 closestPoint;
    closestPoint.x = std::max(cubeMin.x, std::min(sphereCenter.x, cubeMax.x));
    closestPoint.y = std::max(cubeMin.y, std::min(sphereCenter.y, cubeMax.y));
    closestPoint.z = std::max(cubeMin.z, std::min(sphereCenter.z, cubeMax.z));

    // Calculate the distance from the sphere's center to the closest point
    float distanceSquared = glm::dot(closestPoint - sphereCenter, closestPoint - sphereCenter);

    // Check if the distance is less than or equal to the square of the radius
    return distanceSquared <= (sphereRadius * sphereRadius);
}
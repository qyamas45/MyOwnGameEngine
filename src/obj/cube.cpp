#include "objs/cube.h"
#include <algorithm>

Cube::Cube(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, glm::vec3 color, float rotationAngle, bool useCustomColor)
    : scale(scale), rotationAxis(rotationAxis), color(color), rotationAngle(rotationAngle), useCustomColor(useCustomColor)
{
    // Entity's members, set here rather than in the init list (they belong
    // to the base and are already constructed by this point).
    this->position = position;
    this->shader = &ownShader;
    // The mesh spans -scale..+scale on each axis, so the half-extents are
    // scale itself.
    this->collider = new cubeCollider(position, scale);

    setupMesh();
}

void Cube::setupMesh()
{
    // Create a cube with vertices and indices

    vertices = {
        // positions
        -scale.x, -scale.y, -scale.z,
        scale.x, -scale.y, -scale.z,
        scale.x, scale.y, -scale.z,
        -scale.x, scale.y, -scale.z,
        -scale.x, -scale.y, scale.z,
        scale.x, -scale.y, scale.z,
        scale.x, scale.y, scale.z,
        -scale.x, scale.y, scale.z};

    // 12 triangles, 2 per face. Wound counter-clockwise as seen from outside
    // the cube, which is OpenGL's default front-facing orientation.
    indices = {
        0, 2, 1, 0, 3, 2, // back   (-z)
        4, 5, 6, 4, 6, 7, // front  (+z)
        0, 4, 7, 0, 7, 3, // left   (-x)
        1, 2, 6, 1, 6, 5, // right  (+x)
        0, 1, 5, 0, 5, 4, // bottom (-y)
        3, 7, 6, 3, 6, 2  // top    (+y)
    };

    // Generate and bind VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
Cube::~Cube()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete collider;
}

void Cube::clearArrays()
{
    std::vector<float>().swap(vertices);
    std::vector<unsigned int>().swap(indices);
}
void Cube::update(float dt)
{
    // static for now
    position += velocity * dt;
    updateCollider();
}
void Cube::updateCollider()
{
    cube()->position = position;
    cube()->halfExtents = scale;
}
bool Cube::objectCollision(Collider *other)
{
    switch (other->getColliderType())
    {
    case Collider::colliderTypes::SPHERE:
        return collisionDetection::CubeSphereIntersection(cube(), dynamic_cast<sphereCollider *>(other));
    case Collider::colliderTypes::CUBE:
        return collisionDetection::CubeCubeIntersection(cube(), dynamic_cast<cubeCollider *>(other));
    default:
        return false;
    }
}
void Cube::onCollision(Collider *other, const float &dt)
{
    switch (other->getColliderType())
    {
    case Collider::colliderTypes::CUBE:
    {
        cubeCollider *otherCube = dynamic_cast<cubeCollider *>(other);
        if (!otherCube)
            return;

        const glm::vec3 minA = cube()->getMinCoordinates();
        const glm::vec3 maxA = cube()->getMaxCoordinates();
        const glm::vec3 minB = otherCube->getMinCoordinates();
        const glm::vec3 maxB = otherCube->getMaxCoordinates();

        // How deep the two boxes overlap on each axis. Positive on all
        // three axes means they really do intersect.
        glm::vec3 overlap;
        for (int i = 0; i < 3; ++i)
            overlap[i] = std::min(maxA[i], maxB[i]) - std::max(minA[i], minB[i]);

        if (overlap.x <= 0.0f || overlap.y <= 0.0f || overlap.z <= 0.0f)
            return;

        // The shallowest axis is the shortest way out (minimum translation
        // vector); pushing along any other axis would move further than needed.
        int axis = 0;
        if (overlap.y < overlap[axis])
            axis = 1;
        if (overlap.z < overlap[axis])
            axis = 2;

        // Push away from the other cube. Coincident centres fall back to
        // the positive direction so the pair still separates.
        const float sign = (position[axis] < otherCube->position[axis]) ? -1.0f : 1.0f;

        // Half each: the other entity resolves the same pair from its side.
        position[axis] += sign * overlap[axis] * 0.5f;

        updateCollider();
        break;
    }
    case Collider::colliderTypes::SPHERE:
    {

        sphereCollider *otherSphere = dynamic_cast<sphereCollider *>(other);
        if (!otherSphere)
            return;

        const glm::vec3 &sphereCenter = otherSphere->position;
        const float &sphereRadius = otherSphere->radius;

        // Find the closest point on the cube to the sphere's center
        glm::vec3 closestPoint;
        closestPoint.x = std::max(cube()->getMinCoordinates().x, std::min(sphereCenter.x, cube()->getMaxCoordinates().x));
        closestPoint.y = std::max(cube()->getMinCoordinates().y, std::min(sphereCenter.y, cube()->getMaxCoordinates().y));
        closestPoint.z = std::max(cube()->getMinCoordinates().z, std::min(sphereCenter.z, cube()->getMaxCoordinates().z));

        // Calculate the distance from the sphere's center to the closest point

        //when collide and stops, it can cause to output 4.26758e-09, is there a fix?
        //based on the idea, it works, it just that the ball phsyics needs to be implemented on the cube.
        
        float distanceSquared = glm::dot(closestPoint - sphereCenter, closestPoint - sphereCenter);
        ///std::cout << "distanceSquared: " << distanceSquared << std::endl;
        //std::cout << "sphereRadius * sphereRadius: " << sphereRadius * sphereRadius << std::endl;

        // Check if the distance is less than or equal to the square of the radius
        if (distanceSquared >= (sphereRadius * sphereRadius))
            return; // No collision

        // Calculate the distance and the penetration depth
        float distance = std::sqrt(distanceSquared);

        float penetrationDepth = sphereRadius - distance;
  
        if (penetrationDepth <= 0.0f)
            return; // No collision

        position += (closestPoint - sphereCenter) / distance * penetrationDepth;
        //std::cout << position.x << " " << position.y << " " << position.z << std::endl;
        updateCollider();
        break;
    }
    default:
        break;
    }
}
void Cube::setColor(glm::vec3 color)
{
    this->color = color;
    // An explicit color overrides the default white in render().
    useCustomColor = true;
}
void Cube::debug()
{
    std::cout << glm::to_string(position) << std::endl;
}

void Cube::render(const glm::mat4 &view, const glm::mat4 &projection)
{
    shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    if (useCustomColor)
    {
        shader->setVec3("color", color);
    }
    else
    {
        shader->setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f)); // Default color
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
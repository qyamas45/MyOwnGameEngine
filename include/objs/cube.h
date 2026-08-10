#ifndef CUBE_H
#define CUBE_H
#include "entity.h"
#include <string>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
 

class Cube : public Entity
{
public:
    Cube(glm::vec3, glm::vec3, 
        glm::vec3, glm::vec3, float, bool);
    ~Cube();
    

    glm::vec3 getScale() const { return scale; }
    glm::vec3 getColor() const { return color; }
    void update(float) override;
    void updateCollider() override;
    // Cube has no collider yet; returns nullptr, and updateCollisions() skips it.
    Collider* getCollider() override { return collider; }
    void onCollision(Collider* other, const float& dt) override;
    void debug() override;

    void clearArrays();
    void setColor(glm::vec3 color);
    void render(const glm::mat4&, const glm::mat4&) override;

private:
    // Cube's own shader; Entity::shader points at it unless setTexture()
    // swaps in an externally owned one.
    Shader ownShader{"shaders/cube.vs", "shaders/cube.fs"};

    unsigned int VAO, VBO, EBO;

    // Declaration order must match the constructor's init list order.
    glm::vec3 scale;
    glm::vec3 rotationAxis;
    glm::vec3 color;
    float rotationAngle;
    bool useCustomColor = false;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    void setupMesh();
};
#endif
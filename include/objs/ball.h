#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "shader.h"
#include "collider.h"
#include "collider/sphereCollider.h"
#include <vector>
#include <shader.h>
class Ball : public Entity {
public:
    Ball(float x, float y, float z, float radius, 
        int, int, bool, int);
    ~Ball();
    

    Collider* getCollider() override { return collider; }
    void setVelocity(const glm::vec3& v) { velocity = v; }
    void update(float deltaTime) override;
    void updateCollider() override;
    bool objectCollision(Collider* other);
    void onCollision(Collider* other, const float& dt) override;
    
    void buildVerticesSmooth();
    void buildVerticesFlat();
    void clearArrays();
    void addVertex(float x, float y, float z);
    void addNormal(float nx, float ny, float nz);
    void buildInterleavedVertices();
    void changeUpAxis(int from, int to);
    void addTexCoord(float s, float t);
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
    std::vector<float> computeFaceNormal(float x1, float y1, float z1,
                                         float x2, float y2, float z2,
                                         float x3, float y3, float z3);
    void render(const glm::mat4& view, const glm::mat4& projection) override;

    //getter/setters
    // getters/setters
    float getRadius() const                 { return radius; }
    int getSectorCount() const              { return sectorCount; }
    int getStackCount() const               { return stackCount; }
    int getUpAxis() const                   { return upAxis; }
    void set(float radius, int sectorCount, int stackCount, bool smooth=true, int up=3);
    void setRadius(float radius)            { this->radius = radius; }
    void setSectorCount(int sectorCount)    { this->sectorCount = sectorCount; }
    void setStackCount(int stackCount)      { this->stackCount = stackCount; }
    void setSmooth(bool smooth)             { this->smooth = smooth; }
    void setUpAxis(int up)                  { this->upAxis = up; }
   
    // for vertex data
    unsigned int getVertexCount() const         { return (unsigned int)vertices.size() / 3; }
    unsigned int getNormalCount() const         { return (unsigned int)normals.size() / 3; }
    unsigned int getTexCoordCount() const       { return (unsigned int)texCoords.size() / 2; }
    unsigned int getIndexCount() const          { return (unsigned int)indices.size(); }
    unsigned int getLineIndexCount() const      { return (unsigned int)lineIndices.size(); }
    unsigned int getTriangleCount() const       { return getIndexCount() / 3; }
    unsigned int getVertexSize() const          { return (unsigned int)vertices.size() * sizeof(float); }
    unsigned int getNormalSize() const          { return (unsigned int)normals.size() * sizeof(float); }
    unsigned int getTexCoordSize() const        { return (unsigned int)texCoords.size() * sizeof(float); }
    unsigned int getIndexSize() const           { return (unsigned int)indices.size() * sizeof(unsigned int); }
    unsigned int getLineIndexSize() const       { return (unsigned int)lineIndices.size() * sizeof(unsigned int); }
    const float* getVertices() const            { return vertices.data(); }
    const float* getNormals() const             { return normals.data(); }
    const float* getTexCoords() const           { return texCoords.data(); }
    const unsigned int* getIndices() const      { return indices.data(); }
    const unsigned int* getLineIndices() const  { return lineIndices.data(); }
    void debug() override
    {
        std::cout << glm::to_string(position) << std::endl;
    }
private:
    void setupMesh(float, int, int, bool, int);
    // shader, position, collider and anchor are inherited from Entity.

    // Ball's own shader; Entity::shader points at it unless setTexture()
    // swaps in an externally owned one.
    Shader ownShader{"shaders/ball.vs", "shaders/ball.fs"};

    // Entity stores the collider as a base pointer; Ball always builds a
    // sphereCollider, so this is the typed view of it.
    sphereCollider* sphere() const { return static_cast<sphereCollider*>(collider); }

    unsigned int VAO, VBO, EBO;
    float radius;

    glm::vec3 velocity{0.0f};
    int sectorCount; //longtitude
    int stackCount; //latitude
    bool smooth;
    int upAxis;
    std::vector<float>vertices;
    std::vector<float>normals;
    std::vector<float>texCoords;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> lineIndices;
    std::vector<float>interleavedVertices;
    int interleavedStride;
};

#endif

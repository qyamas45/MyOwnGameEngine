#ifndef GAME_H
#define GAME_H
#include "core/application.h"
#include "entity.h"
#include "objs/ball.h"
#include "objs/cube.h"
#include <vector>
#include <memory>
#include <iostream>
#include <shader.h>
#include "core/camera.h"
#include "collider.h"

void updateCollisions(std::vector<std::unique_ptr<Entity>>& objects, float deltaTime)
{
    for(std::size_t i{0}; i < objects.size(); ++i)
    {
        for(std::size_t j{i+1}; j < objects.size(); ++j)
        {
            Collider* a = objects[i]->getCollider();
            Collider* b = objects[j]->getCollider();

            // Entities without a collider don't participate.
            if(!a || !b)
                continue;

            if(a->objectCollision(b))
            {
                //std::cout << "HIT: " << i << " <-> " << j << std::endl;

                // Both sides must resolve against the SAME pre-contact state.
                // onCollision() writes its correction into the collider, so
                // letting i go first would hand j a pair that no longer
                // overlaps and j would early-out without moving. Rewind i
                // while j resolves, then re-apply i's correction.
                const glm::vec3 preA = objects[i]->getPosition();

                objects[i]->onCollision(b, deltaTime);
                const glm::vec3 resolvedA = objects[i]->getPosition();

                objects[i]->setPosition(preA);
                objects[j]->onCollision(a, deltaTime);
                objects[i]->setPosition(resolvedA);
            }
        }
    }
}
class Game : public Application
{
public:
    Game(int width, int height, const char *title) : Application(width, height, title)
    {
        //objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 9.0f, 0.2f, 1.0f,36, 18, true, 3)));
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 6.0f, 0.2f, 1.0f,36, 18, true, 3)));
        objects.push_back(std::unique_ptr<Cube>(new Cube(glm::vec3(-0.0f, -3.0f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.31f), 45.0f, false)));
        objects.push_back(std::unique_ptr<Cube>(new Cube(glm::vec3(-0.0f, 0.1f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.31f), 45.0f, false)));
        //  DEBUGGING PURPOSES:
        //std::cout << "Game initialized with " << objects.size() << " objects." << std::endl;
    }
    void onUpdate(float deltaTime) override
    {
        val -= 0.01f;
        // Update game logic here
        for (auto &obj : objects)
        {
            obj->update(deltaTime);
            //obj->debug();
        }
        //debugging to check collisions
        //objects[0]->setPosition(glm::vec3(0.0f, val, 0.0f));
        updateCollisions(objects, deltaTime);
    }
    void onRender(const glm::mat4& view, const glm::mat4& projection) override
    {
        for (auto &obj : objects)
        {
            obj->render(view, projection);
        }
    }
    
private:
    std::vector<std::unique_ptr<Entity>> objects;
    float  val = 6.0f;
    
};

#endif

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

            // Entities without a collider (e.g. Cube) don't participate.
            if(!a || !b)
                continue;

            if(a->objectCollision(b))
            {
                //std::cout << "HIT: " << i << " <-> " << j << std::endl;
                objects[i]->onCollision(b, deltaTime);
                objects[j]->onCollision(a, deltaTime);
            }
        }
    }
}
class Game : public Application
{
public:
    Game(int width, int height, const char *title) : Application(width, height, title)
    {
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 0.0f, 0.2f, 1.0f,36, 18, true, 3)));
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 3.0f, 0.2f, 1.0f,36, 18, true, 3)));
        objects.push_back(std::unique_ptr<Cube>(new Cube(glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.5f, 0.31f), 45.0f, false)));
        //  DEBUGGING PURPOSES:
        //std::cout << "Game initialized with " << objects.size() << " objects." << std::endl;
    }
    void onUpdate(float deltaTime) override
    {
        // Update game logic here
        for (auto &obj : objects)
        {
            obj->update(deltaTime);
            //obj->debug();
        }
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

    
};

#endif

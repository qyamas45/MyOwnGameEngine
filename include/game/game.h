#ifndef GAME_H
#define GAME_H
#include "application.h"
#include "entity.h"
#include "ball.h"
#include <vector>
#include <memory>
#include <iostream>
#include <shader.h>
#include "camera.h"
#include "collider.h"
class Game : public Application
{
public:
    Game(int width, int height, const char *title) : Application(width, height, title)
    {
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 0.0f, 0.2f, 1.0f,36, 18, true, 3)));
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 3.0f, 0.2f, 1.0f,36, 18, true, 3)));
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
        for(std::size_t i{0}; i < objects.size(); ++i)
        {
            for(std::size_t j{i+1}; j < objects.size(); ++j)
            {
                Collider* a = objects[i]->getCollider();
                Collider* b = objects[i]->getCollider();

                if(a->objectCollision(b))
                {
                    //std::cout << "HIT: " << i << " <-> " << j << std::endl;
                    objects[i]->onCollision(b, deltaTime);
                    objects[j]->onCollision(a, deltaTime);
                }
            }
        }
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

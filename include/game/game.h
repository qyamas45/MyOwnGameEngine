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


class Game : public Application {
public:
    Game(int width, int height, const char* title) : Application(width, height, title) {
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 0.0f, 0.2f, 20.0f)));
        std::cout << "Game initialized with " << objects.size() << " objects." << std::endl;
    }
    void onUpdate(float deltaTime) override {
        // Update game logic here
        for (auto& obj : objects) {
            obj->update(deltaTime);
        }
    }
    void onRender() override {
        // Render game objects here
        for (auto& obj : objects) {
            obj->render();
        }
    }
private:
    std::vector<std::unique_ptr<Entity>> objects;
    
     
Camera camera(glm::vec3(3.0f, 4.0f, 8.0f), 
              glm::vec3(0.0f, 1.0f, 0.0f), 
              -90.0f, -45.0f);
 
};


#endif

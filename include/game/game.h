#ifndef GAME_H
#define GAME_H
#include "application.h"
#include "entity.h"
#include "ball.h"
#include <vector>
#include <memory>


class Game : public Application {
public:
    Game(int width, int height, const char* title) : Application(width, height, title) {
        objects.push_back(std::unique_ptr<Ball>(new Ball(0.0f, 0.0f, 3.0f, 20.0f)));
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
};


#endif

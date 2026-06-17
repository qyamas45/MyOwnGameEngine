#ifndef GAME_H
#define GAME_H
#include "window.h"
class Game : public Window {
public:
    Game(int width, int height, const char* title) : Window(width, height, title) {}
    void onUpdate(float deltaTime) override {
        // Update game logic here
    }
    void onRender() override {
        // Render game objects here
    }
};


#endif

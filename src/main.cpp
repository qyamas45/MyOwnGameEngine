#include <iostream>
#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game.h"

int main() {
    Game game(800, 600, "Game Engine");
    game.run();
    return 0;
     
}

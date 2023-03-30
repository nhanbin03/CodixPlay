#ifndef APPLICATION_H
#define APPLICATION_H

#include "StateStack.h"

#include "raylib.h"

const float WINDOW_WIDTH = 1440;
const float WINDOW_HEIGHT = 950;
const char* WINDOW_TITLE = "VisuAlgo";

const int FPS = 60;
class Application {
public:
    Application();
    void run();

private:
    void update(float dt);
    void render();

private:
    StateStack mStateStack;
};

#endif // APPLICATION_H

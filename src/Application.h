#ifndef APPLICATION_H
#define APPLICATION_H

#include "StateStack.h"

#include "raylib.h"


class Application {

public:
    const float WINDOW_WIDTH = 1440;
    const float WINDOW_HEIGHT = 950;
    const char *WINDOW_TITLE = "VisuAlgo";

    const int FPS = 60;

public:
    Application();
    ~Application();
    
    void run();

private:
    void update(float dt);
    void render();

private:
    StateStack mStateStack;
};

#endif // APPLICATION_H

#ifndef APPLICATION_H
#define APPLICATION_H

#include "StateStack.h"

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

#ifndef STACKSTATE_H
#define STACKSTATE_H

#include "States/State.h"

class StackState : public State {
public:
    StackState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STACKSTATE_H

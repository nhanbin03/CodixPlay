#ifndef STATES_STACKSTATE_H
#define STATES_STACKSTATE_H

#include "State.h"

class StackState : public State {
public:
    StackState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    Visualization mVisualization;
    ActionContainer mActions;
};

#endif // STATES_STACKSTATE_H

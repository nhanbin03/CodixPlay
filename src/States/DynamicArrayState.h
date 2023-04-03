#ifndef STATES_DYNAMICARRAYSTATE_H
#define STATES_DYNAMICARRAYSTATE_H

#include "State.h"

class DynamicArrayState : public State {
public:
    DynamicArrayState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STATES_DYNAMICARRAYSTATE_H

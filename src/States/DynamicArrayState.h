#ifndef DYNAMICARRAYSTATE_H
#define DYNAMICARRAYSTATE_H

#include "../State.h"

class DynamicArrayState : public State
{
public:
    DynamicArrayState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // DYNAMICARRAYSTATE_H

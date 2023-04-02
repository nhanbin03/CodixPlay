#ifndef STATES_STATICARRAYSTATE_H
#define STATES_STATICARRAYSTATE_H

#include "../State.h"

class StaticArrayState : public State {
public:
    StaticArrayState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STATES_STATICARRAYSTATE_H

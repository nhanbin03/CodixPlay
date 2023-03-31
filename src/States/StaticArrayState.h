#ifndef STATICARRAYSTATE_H
#define STATICARRAYSTATE_H

#include "../State.h"

class StaticArrayState : public State {
public:
    StaticArrayState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STATICARRAYSTATE_H



#ifndef STATES_HOMESTATE_H
#define STATES_HOMESTATE_H

#include "State.h"

class HomeState : public State {
public:
    HomeState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STATES_HOMESTATE_H

#ifndef HOMESTATE_H
#define HOMESTATE_H

#include "../State.h"

class HomeState : public State
{
public:
    HomeState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // HOMESTATE_H

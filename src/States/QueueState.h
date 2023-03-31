#ifndef QUEUESTATE_H
#define QUEUESTATE_H

#include "../State.h"

class QueueState : public State
{
public:
    QueueState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // QUEUESTATE_H

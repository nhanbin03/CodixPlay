#ifndef STATES_QUEUESTATE_H
#define STATES_QUEUESTATE_H

#include "State.h"

class QueueState : public State {
public:
    QueueState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    Visualization mVisualization;
    ActionContainer mActions;
};

#endif // STATES_QUEUESTATE_H

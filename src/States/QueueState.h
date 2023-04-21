#ifndef STATES_QUEUESTATE_H
#define STATES_QUEUESTATE_H

#include "../Algorithms/QueueAlgo.h"
#include "State.h"

class QueueState : public State {
public:
    QueueState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    QueueAlgo mAlgo;
    Visualization mVisualization;
    ActionContainer mActions;

private:
    void populateInitialize();
    void populateInsert();
    void populateRemove();
    void populateSearch();
};

#endif // STATES_QUEUESTATE_H

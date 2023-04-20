#ifndef STATES_STACKSTATE_H
#define STATES_STACKSTATE_H

#include "../Algorithms/StackAlgo.h"
#include "State.h"

class StackState : public State {
public:
    StackState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    StackAlgo mAlgo;
    Visualization mVisualization;
    ActionContainer mActions;

private:
    void populateInitialize();
    void populateInsert();
    void populateRemove();
    void populateSearch();
};

#endif // STATES_STACKSTATE_H

#ifndef STATES_DYNAMICARRAYSTATE_H
#define STATES_DYNAMICARRAYSTATE_H

#include "../Algorithms/DynamicArrayAlgo.h"
#include "State.h"

class DynamicArrayState : public State {
public:
    DynamicArrayState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    Visualization mVisualization;
    DynamicArrayAlgo mAlgo;
    ActionContainer mActions;

private:
    void populateInitialize();
    void populateInsert();
    void populateRemove();
    void populateUpdate();
    void populateSearch();
};

#endif // STATES_DYNAMICARRAYSTATE_H

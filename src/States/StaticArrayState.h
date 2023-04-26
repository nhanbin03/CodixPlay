#ifndef STATES_STATICARRAYSTATE_H
#define STATES_STATICARRAYSTATE_H

#include "../Algorithms/StaticArrayAlgo.h"
#include "State.h"

class StaticArrayState : public State {
public:
    StaticArrayState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    Visualization mVisualization;
    StaticArrayAlgo mAlgo;
    ActionContainer mActions;

private:
    void populateInitialize();
    void populateInsert();
    void populateRemove();
    void populateUpdate();
    void populateSearch();
};

#endif // STATES_STATICARRAYSTATE_H

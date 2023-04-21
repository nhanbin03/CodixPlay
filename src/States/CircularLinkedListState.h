#ifndef STATES_CIRCULARLINKEDLISTSTATE_H
#define STATES_CIRCULARLINKEDLISTSTATE_H

#include "../Algorithms/CircularLinkedListAlgo.h"
#include "State.h"

class CircularLinkedListState : public State {
public:
    CircularLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    CircularLinkedListAlgo mAlgo;
    Visualization mVisualization;
    ActionContainer mActions;

private:
    void populateInitialize();
    void populateInsert();
    void populateRemove();
    void populateUpdate();
    void populateSearch();
};

#endif // STATES_CIRCULARLINKEDLISTSTATE_H

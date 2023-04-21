#ifndef STATES_DOUBLYLINKEDLISTSTATE_H
#define STATES_DOUBLYLINKEDLISTSTATE_H

#include "../Algorithms/DoublyLinkedListAlgo.h"
#include "State.h"

class DoublyLinkedListState : public State {
public:
    DoublyLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    DoublyLinkedListAlgo mAlgo;
    Visualization mVisualization;
    ActionContainer mActions;

private:
    void populateInitialize();
    void populateInsert();
    void populateRemove();
    void populateUpdate();
    void populateSearch();
};

#endif // STATES_DOUBLYLINKEDLISTSTATE_H

#ifndef STATES_DOUBLYLINKEDLISTSTATE_H
#define STATES_DOUBLYLINKEDLISTSTATE_H

#include "State.h"

class DoublyLinkedListState : public State {
public:
    DoublyLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    Visualization mVisualization;
    ActionContainer mActions;
};

#endif // STATES_DOUBLYLINKEDLISTSTATE_H

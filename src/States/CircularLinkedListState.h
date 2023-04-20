#ifndef STATES_CIRCULARLINKEDLISTSTATE_H
#define STATES_CIRCULARLINKEDLISTSTATE_H

#include "State.h"

class CircularLinkedListState : public State {
public:
    CircularLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    Visualization mVisualization;
    ActionContainer mActions;
};

#endif // STATES_CIRCULARLINKEDLISTSTATE_H

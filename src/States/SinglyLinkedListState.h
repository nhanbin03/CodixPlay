#ifndef STATES_SINGLYLINKEDLISTSTATE_H
#define STATES_SINGLYLINKEDLISTSTATE_H

#include "../State.h"

class SinglyLinkedListState : public State {
public:
    SinglyLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STATES_SINGLYLINKEDLISTSTATE_H

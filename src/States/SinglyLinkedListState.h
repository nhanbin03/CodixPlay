#ifndef STATES_SINGLYLINKEDLISTSTATE_H
#define STATES_SINGLYLINKEDLISTSTATE_H

#include "../Algorithms/SinglyLinkedListAlgo.h"
#include "State.h"

#include "../ActionContainer.h"
#include "../GUIComponents/Button.h"

class SinglyLinkedListState : public State {
public:
    SinglyLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();

private:
    SinglyLinkedListAlgo mAlgo;
    Button mButton;
    ActionContainer mActions;
};

#endif // STATES_SINGLYLINKEDLISTSTATE_H

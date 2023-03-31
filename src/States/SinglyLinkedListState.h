#ifndef SINGLYLINKEDLISTSTATE_H
#define SINGLYLINKEDLISTSTATE_H

#include "../State.h"

class SinglyLinkedListState : public State
{
public:
    SinglyLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // SINGLYLINKEDLISTSTATE_H

#ifndef DOUBLYLINKEDLISTSTATE_H
#define DOUBLYLINKEDLISTSTATE_H

#include "../State.h"

class DoublyLinkedListState : public State
{
public:
    DoublyLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // DOUBLYLINKEDLISTSTATE_H

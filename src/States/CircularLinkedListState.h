#ifndef CIRCULARLINKEDLISTSTATE_H
#define CIRCULARLINKEDLISTSTATE_H

#include "../State.h"

class CircularLinkedListState : public State {
public:
    CircularLinkedListState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // CIRCULARLINKEDLISTSTATE_H

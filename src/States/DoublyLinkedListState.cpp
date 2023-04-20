#include "DoublyLinkedListState.h"

#include "raylib.h"

DoublyLinkedListState::DoublyLinkedListState(StateStack &stack, Context context)
: State(stack, context)
, mActions("Doubly Linked List") {
}

bool DoublyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);
    return true;
}

void DoublyLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

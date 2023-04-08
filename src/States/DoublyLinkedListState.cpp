#include "DoublyLinkedListState.h"

#include "raylib.h"

DoublyLinkedListState::DoublyLinkedListState(StateStack &stack, Context context)
: State(stack, context) {
}

bool DoublyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    return true;
}

void DoublyLinkedListState::draw() {
    ClearBackground(RAYWHITE);
    mVisualization.draw();
}

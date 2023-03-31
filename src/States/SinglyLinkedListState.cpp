#include "SinglyLinkedListState.h"

#include "raylib.h"

SinglyLinkedListState::SinglyLinkedListState(StateStack &stack, Context context)
: State(stack, context) {
}

bool SinglyLinkedListState::update(float dt) {
    return true;
}

void SinglyLinkedListState::draw() {
    ClearBackground(RAYWHITE);
}

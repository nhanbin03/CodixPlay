#include "SinglyLinkedListState.h"

#include "raylib.h"

#include <iostream>

SinglyLinkedListState::SinglyLinkedListState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization) {
}

bool SinglyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    return true;
}

void SinglyLinkedListState::draw() {
    ClearBackground(RAYWHITE);
    mVisualization.draw();
}

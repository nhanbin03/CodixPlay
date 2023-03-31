#include "StackState.h"

#include "raylib.h"

StackState::StackState(StateStack &stack, Context context)
: State(stack, context) {
}

bool StackState::update(float dt) {
    return true;
}

void StackState::draw() {
    ClearBackground(RAYWHITE);
}

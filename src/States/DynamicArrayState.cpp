#include "DynamicArrayState.h"

#include "raylib.h"

DynamicArrayState::DynamicArrayState(StateStack &stack, Context context)
: State(stack, context) {
}

bool DynamicArrayState::update(float dt) {
    return true;
}

void DynamicArrayState::draw() {
    ClearBackground(RAYWHITE);
}

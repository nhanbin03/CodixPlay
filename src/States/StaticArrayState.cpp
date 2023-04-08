#include "StaticArrayState.h"

#include "raylib.h"

StaticArrayState::StaticArrayState(StateStack &stack, Context context)
: State(stack, context) {
}

bool StaticArrayState::update(float dt) {
    mVisualization.update(dt);
    return true;
}

void StaticArrayState::draw() {
    ClearBackground(RAYWHITE);
    mVisualization.draw();
}

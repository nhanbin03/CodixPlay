#include "QueueState.h"

#include "raylib.h"

QueueState::QueueState(StateStack &stack, Context context)
: State(stack, context) {
}

bool QueueState::update(float dt) {
    mVisualization.update(dt);
    return true;
}

void QueueState::draw() {
    ClearBackground(RAYWHITE);
    mVisualization.draw();
}

#include "QueueState.h"

#include "raylib.h"

QueueState::QueueState(StateStack &stack, Context context)
: State(stack, context)
, mActions("Queue") {
}

bool QueueState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);

    return true;
}

void QueueState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

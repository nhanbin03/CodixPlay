#include "StackState.h"

#include "raylib.h"

StackState::StackState(StateStack &stack, Context context)
: State(stack, context)
, mActions("Stack") {
}

bool StackState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);
    return true;
}

void StackState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

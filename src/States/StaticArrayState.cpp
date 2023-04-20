#include "StaticArrayState.h"

#include "raylib.h"

StaticArrayState::StaticArrayState(StateStack &stack, Context context)
: State(stack, context)
, mActions("Static Array") {
}

bool StaticArrayState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);
    return true;
}

void StaticArrayState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

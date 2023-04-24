#include "DynamicArrayState.h"

#include "raylib.h"

#include <iostream>

DynamicArrayState::DynamicArrayState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization)
, mActions("Dynamic Array") {
}

bool DynamicArrayState::update(float dt) {
    mNavBar.update(dt);
    mVisualization.update(dt);
    mActions.update(dt);
    return true;
}

void DynamicArrayState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mNavBar.draw();
    mVisualization.draw();
    mActions.draw();
}

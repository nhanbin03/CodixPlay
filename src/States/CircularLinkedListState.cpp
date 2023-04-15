#include "CircularLinkedListState.h"

#include "raylib.h"

CircularLinkedListState::CircularLinkedListState(StateStack &stack,
                                                 Context context)
: State(stack, context) {
}

bool CircularLinkedListState::update(float dt) {
    mVisualization.update(dt);
    return true;
}

void CircularLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
}

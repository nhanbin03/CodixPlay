#include "SinglyLinkedListState.h"

#include "raylib.h"

#include <iostream>

SinglyLinkedListState::SinglyLinkedListState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization) {
    mButton.setRect({700, 500, 400, 100});
    mButton.setText("Add");
    mButton.setColor(RAYWHITE);
    mButton.setContentColor(BLACK);
    mButton.setBorderThickness(2);
    mButton.setBorderColor(BLACK);

    mButton.setCallback([this]() {
        this->mAlgo.addLast(rand() % 100);
    });
}

bool SinglyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    mButton.update(dt);
    return true;
}

void SinglyLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mButton.draw();
}

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

    mAlgo.addFirst(0);
    mAlgo.addFirst(0);
    mAlgo.addFirst(0);
    mAlgo.addFirst(0);
    mButton.setCallback([this]() {
        this->mAlgo.addMiddle(3, rand() % 100);
    });

    mActionTab.addActionSelector("Insert at the beginning", {},
                                 [](std::map<std::string, std::string>) {});
    mActionTab.addActionSelector("Insert in the middle ", {},
                                 [](std::map<std::string, std::string>) {});
    mActionTab.addActionSelector("Insert at the end", {},
                                 [](std::map<std::string, std::string>) {});
}

bool SinglyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    mActionTab.update(dt);
    mButton.update(dt);

    return true;
}

void SinglyLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActionTab.draw();
    mButton.draw();
}

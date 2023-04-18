#include "SinglyLinkedListState.h"

#include "raylib.h"

#include <iostream>
#include <regex>

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

    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Update);
    mActions.addTab(ActionContainer::TabID::Search);

    mActions.getTab(ActionContainer::TabID::Insert)
        ->addActionSelector("Insert at the beginning ", {},
                            [](std::map<std::string, std::string>) {});
    mActions.getTab(ActionContainer::TabID::Insert)
        ->addActionSelector("Insert in the middle",
                            {(ActionBox::Input){"pos = ", "pos",
                                                [](std::string) {
                                                    return true;
                                                },
                                                60},
                             (ActionBox::Input){"value = ", "value",
                                                [](std::string) {
                                                    return true;
                                                },
                                                60}},
                            [this](std::map<std::string, std::string> data) {
                                int pos = std::stoi(data["pos"]);
                                int value = std::stoi(data["value"]);
                                this->mAlgo.addMiddle(pos, value);
                            });
    mActions.getTab(ActionContainer::TabID::Insert)
        ->addActionSelector("Insert at the end", {},
                            [](std::map<std::string, std::string>) {});
}

bool SinglyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);
    mButton.update(dt);

    return true;
}

void SinglyLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
    mButton.draw();
}

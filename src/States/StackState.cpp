#include "StackState.h"

#include "raylib.h"

#include <iostream>

StackState::StackState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization)
, mActions("Stack") {
    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Search);

    populateInsert();
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

void StackState::populateInsert() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Insert);

    // Push option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Push", {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.push(value);
                return true;
            });
    }
}

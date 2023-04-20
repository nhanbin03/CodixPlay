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
    populateRemove();
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
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_STACK_SIZE) {
                    std::cout << "Max size reached!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.push(value);
                return true;
            });
    }
}

void StackState::populateRemove() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Remove);

    // Pop option
    {
        curTab->addActionSelector("Pop", {},
                                  [this](ActionBox::InputData, bool) {
                                      this->mAlgo.pop();
                                      return true;
                                  });
    }
}

#include "CircularLinkedListState.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

CircularLinkedListState::CircularLinkedListState(StateStack &stack,
                                                 Context context)
: State(stack, context)
, mAlgo(mVisualization)
, mActions("Circular Linked List") {
    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Update);
    mActions.addTab(ActionContainer::TabID::Search);

    populateInsert();
    populateRemove();
}

bool CircularLinkedListState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);
    return true;
}

void CircularLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

void CircularLinkedListState::populateInsert() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Insert);

    // Insert at head option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Insert at head",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_DS_SIZE) {
                    std::cout << "Max size reached!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.addHead(value);
                return true;
            });
    }
}

void CircularLinkedListState::populateRemove() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Remove);

    // Delete at head option
    {
        curTab->addActionSelector(
            "Delete at head", {}, [this](ActionBox::InputData, bool) {
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return false;
                }
                this->mAlgo.deleteHead();
                return true;
            });
    }
}

#include "SinglyLinkedListState.h"

#include "raylib.h"

#include <iostream>
#include <regex>

SinglyLinkedListState::SinglyLinkedListState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization) {
    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Update);
    mActions.addTab(ActionContainer::TabID::Search);

    populateInsert();
    populateRemove();
}

bool SinglyLinkedListState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);

    return true;
}

void SinglyLinkedListState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

void SinglyLinkedListState::populateInsert() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Insert);

    // Insert at the beginning option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Insert at the beginning ",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "Max size reached!\n";
                    return;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.addFirst(value);
            });
    }

    // Insert in the middle option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func =
                InputBox::integerValidator(1, this->mAlgo.getDSSize() - 1);
            return func(str);
        };
        auto valueValidator = InputBox::integerValidator(0, 99);

        curTab->addActionSelector(
            "Insert in the middle",
            {ActionBox::Input("pos = ", "pos", posValidator, 60),
             ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "Max size reached!\n";
                    return;
                }
                int pos = std::stoi(data["pos"]);
                int value = std::stoi(data["value"]);
                this->mAlgo.addMiddle(pos, value);
            });
    }

    // Insert at the end option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Insert at the end ",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "Max size reached!\n";
                    return;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.addLast(value);
            });
    }
}

void SinglyLinkedListState::populateRemove() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Remove);

    // Delete at the beginning option
    {
        curTab->addActionSelector(
            "Delete at the beginning", {},
            [this](std::map<std::string, std::string>, bool) {
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return;
                }
                this->mAlgo.deleteFirst();
            });
    }

    // Delete in the middle option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func =
                InputBox::integerValidator(1, this->mAlgo.getDSSize() - 2);
            return func(str);
        };
        curTab->addActionSelector(
            "Delete in the middle",
            {ActionBox::Input("pos = ", "pos", posValidator, 60)},
            [this](std::map<std::string, std::string> data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return;
                }
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return;
                }
                int pos = std::stoi(data["pos"]);
                this->mAlgo.deleteMiddle(pos);
            });
    }

    // Delete the end option
    {
        curTab->addActionSelector(
            "Delete at the end", {},
            [this](std::map<std::string, std::string>, bool) {
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return;
                }
                this->mAlgo.deleteLast();
            });
    }
}

#include "SinglyLinkedListState.h"

#include "raylib.h"

#include <iostream>
#include <regex>
#include <sstream>

SinglyLinkedListState::SinglyLinkedListState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization)
, mActions("Singly Linked List") {
    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Update);
    mActions.addTab(ActionContainer::TabID::Search);

    populateInsert();
    populateRemove();
    populateInitialize();
    populateUpdate();
    populateSearch();
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

void SinglyLinkedListState::populateInitialize() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Initialize);

    // Initialize randomly (fixed size) option
    {
        auto sizeValidator = InputBox::integerValidator(0, 7);
        curTab->addActionSelector(
            "Initialize randomly (fixed size)",
            {ActionBox::Input("size = ", "size", sizeValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int size = std::stoi(data["size"]);
                this->mAlgo.initializeRandomFixSize(size);
                return true;
            });
    }

    // Initialize by manual input option
    {
        auto listValidator = InputBox::integerSpaceSeparatedListValidator();
        curTab->addActionSelector(
            "Initialize by manual input",
            {ActionBox::Input("list = ", "list", listValidator, 220)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                std::stringstream ss(data["list"]);
                int element;
                std::vector<int> list;
                while (ss >> element) {
                    if (element < 0 || element > 99) {
                        std::cout << "Invalid input!\n";
                        return false;
                    }
                    list.push_back(element);
                }
                if (list.size() > this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "List is too long!\n";
                    return false;
                }
                this->mAlgo.initialize(list);
                return true;
            });
    }
}

void SinglyLinkedListState::populateInsert() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Insert);

    // Insert at the beginning option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Insert at the beginning",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "Max size reached!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.addFirst(value);
                return true;
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
                    return false;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "Max size reached!\n";
                    return false;
                }
                int pos = std::stoi(data["pos"]);
                int value = std::stoi(data["value"]);
                this->mAlgo.addMiddle(pos, value);
                return true;
            });
    }

    // Insert at the end option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Insert at the end",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_LIST_SIZE) {
                    std::cout << "Max size reached!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.addLast(value);
                return true;
            });
    }
}

void SinglyLinkedListState::populateRemove() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Remove);

    // Delete at the beginning option
    {
        curTab->addActionSelector(
            "Delete at the beginning", {}, [this](ActionBox::InputData, bool) {
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return false;
                }
                this->mAlgo.deleteFirst();
                return true;
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
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return false;
                }
                int pos = std::stoi(data["pos"]);
                this->mAlgo.deleteMiddle(pos);
                return true;
            });
    }

    // Delete the end option
    {
        curTab->addActionSelector(
            "Delete at the end", {}, [this](ActionBox::InputData, bool) {
                if (this->mAlgo.getDSSize() == 0) {
                    std::cout << "No element to delete!\n";
                    return false;
                }
                this->mAlgo.deleteLast();
                return true;
            });
    }
}

void SinglyLinkedListState::populateUpdate() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Update);

    // Update node value option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func =
                InputBox::integerValidator(0, this->mAlgo.getDSSize() - 1);
            return func(str);
        };
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Update node value",
            {ActionBox::Input("pos = ", "pos", posValidator, 60),
             ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int pos = std::stoi(data["pos"]);
                int value = std::stoi(data["value"]);
                this->mAlgo.updateValue(pos, value);
                return true;
            });
    }
}

void SinglyLinkedListState::populateSearch() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Search);

    // Search for value option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Search for value",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.searchValue(value);
                return true;
            });
    }
}

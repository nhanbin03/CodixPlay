#include "QueueState.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

QueueState::QueueState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization)
, mActions("Queue") {
    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Search);

    populateInitialize();
    populateInsert();
    populateRemove();
    populateSearch();
}

bool QueueState::update(float dt) {
    mVisualization.update(dt);
    mActions.update(dt);

    return true;
}

void QueueState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mVisualization.draw();
    mActions.draw();
}

void QueueState::populateInitialize() {
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
                if (list.size() > this->mAlgo.MAX_DS_SIZE) {
                    std::cout << "List is too long!\n";
                    return false;
                }
                this->mAlgo.initialize(list);
                return true;
            });
    }
}

void QueueState::populateInsert() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Insert);

    // Enqueue option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Enqueue",
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
                this->mAlgo.enqueue(value);
                return true;
            });
    }
}

void QueueState::populateRemove() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Remove);

    // Dequeue option
    {
        curTab->addActionSelector("Dequeue", {},
                                  [this](ActionBox::InputData, bool) {
                                      if (this->mAlgo.getDSSize() == 0) {
                                          std::cout << "No element to pop!\n";
                                          return false;
                                      }
                                      this->mAlgo.dequeue();
                                      return true;
                                  });
    }
}

void QueueState::populateSearch() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Search);

    // Get front value option
    {
        curTab->addActionSelector("Get front value", {},
                                  [this](ActionBox::InputData, bool) {
                                      this->mAlgo.getFront();
                                      return true;
                                  });
    }
}

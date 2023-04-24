#include "DynamicArrayState.h"

#include "raylib.h"

#include <iostream>

DynamicArrayState::DynamicArrayState(StateStack &stack, Context context)
: State(stack, context)
, mAlgo(mVisualization)
, mActions("Dynamic Array") {
    mActions.addTab(ActionContainer::TabID::Initialize);
    mActions.addTab(ActionContainer::TabID::Insert);
    mActions.addTab(ActionContainer::TabID::Remove);
    mActions.addTab(ActionContainer::TabID::Update);
    mActions.addTab(ActionContainer::TabID::Search);

    populateInitialize();
}

bool DynamicArrayState::update(float dt) {
    mNavBar.update(dt);
    mVisualization.update(dt);
    mActions.update(dt);
    return true;
}

void DynamicArrayState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mNavBar.draw();
    mVisualization.draw();
    mActions.draw();
}

void DynamicArrayState::populateInitialize() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Initialize);

    // Initialize randomly (fixed size) option
    {
        auto sizeValidator = InputBox::integerValidator(0, 8);
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

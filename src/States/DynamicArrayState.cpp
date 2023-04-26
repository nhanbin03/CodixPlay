#include "DynamicArrayState.h"
#include "../Helper.h"

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
    populateInsert();
    populateRemove();
    populateUpdate();
    populateSearch();
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
        auto sizeValidator = InputBox::integerValidator(0, mAlgo.MAX_DS_SIZE);
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

    // Initialize by file input option
    {
        auto pathValidator = [](std::string str) {
            return str != "";
        };
        curTab->addActionSelector(
            "Initialize by file input",
            {ActionBox::Input("", "path", pathValidator, 220)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                std::vector<int> list = readListFromFile<int>(data["path"]);
                this->mAlgo.initialize(list);
                return true;
            },
            true);
    }
}

void DynamicArrayState::populateInsert() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Insert);

    // Insert an element option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func = InputBox::integerValidator(0, this->mAlgo.getDSSize());
            return func(str);
        };
        auto valueValidator = InputBox::integerValidator(0, 99);

        curTab->addActionSelector(
            "Insert an element",
            {ActionBox::Input("pos = ", "pos", posValidator, 60),
             ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                if (this->mAlgo.getDSSize() == this->mAlgo.MAX_DS_SIZE) {
                    std::cout << "Max size reached!\n";
                    return false;
                }
                int pos = std::stoi(data["pos"]);
                int value = std::stoi(data["value"]);
                this->mAlgo.addElement(pos, value);
                return true;
            });
    }

    // Reserve more space option
    {
        auto newCapValidator = InputBox::integerValidator(1, mAlgo.MAX_DS_SIZE);
        curTab->addActionSelector(
            "Reserve more space",
            {ActionBox::Input("newCap = ", "newCap", newCapValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int newCap = std::stoi(data["newCap"]);
                this->mAlgo.reserveSpace(newCap);
                return true;
            });
    }
}

void DynamicArrayState::populateRemove() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Remove);

    // Delete an element option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func =
                InputBox::integerValidator(0, this->mAlgo.getDSSize() - 1);
            return func(str);
        };
        curTab->addActionSelector(
            "Delete an element",
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
                this->mAlgo.deleteElement(pos);
                return true;
            });
    }
}

void DynamicArrayState::populateUpdate() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Update);

    // Update element value option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func =
                InputBox::integerValidator(0, this->mAlgo.getDSSize() - 1);
            return func(str);
        };
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Update element value",
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

void DynamicArrayState::populateSearch() {
    ActionTab::Ptr curTab = mActions.getTab(ActionContainer::TabID::Search);

    // Access an element option
    {
        auto posValidator = [this](std::string str) -> bool {
            auto func =
                InputBox::integerValidator(0, this->mAlgo.getDSSize() - 1);
            return func(str);
        };
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Access an element",
            {ActionBox::Input("pos = ", "pos", posValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int pos = std::stoi(data["pos"]);
                this->mAlgo.accessElement(pos);
                return true;
            });
    }

    // Search for first value option
    {
        auto valueValidator = InputBox::integerValidator(0, 99);
        curTab->addActionSelector(
            "Search for first value",
            {ActionBox::Input("value = ", "value", valueValidator, 60)},
            [this](ActionBox::InputData data, bool status) {
                if (!status) {
                    std::cout << "Invalid input!\n";
                    return false;
                }
                int value = std::stoi(data["value"]);
                this->mAlgo.searchFirstValue(value);
                return true;
            });
    }
}

#include "ActionTab.h"

#include <iostream>

ActionTab::ActionTab() {
    mRect = {985, 181, 455, 436};
    mColor = AppColor::BACKGROUND_4;
}

void ActionTab::update(float dt) {
    for (auto &action : mActions) {
        action.update(dt);
    }
}

void ActionTab::draw() {
    DrawRectangleRec(mRect, mColor);
    for (auto &action : mActions) {
        action.draw();
    }
}

void ActionTab::addActionSelector(
    std::string title, std::vector<ActionBox::Input> inputs,
    std::function<void(std::map<std::string, std::string>)> onSubmit) {
    const int curIndex = mActions.size();
    auto onSelect = [this, curIndex]() {
        this->select(curIndex);
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    };
    ActionBox newBox = ActionBox(title, inputs, onSubmit, onSelect);
    int startingY;
    if (mActions.empty()) {
        startingY = 200;
    } else {
        startingY = mActions.back().getPosition().y + 87;
    }
    newBox.setRect((Rectangle){1020, startingY, 385, 77});
    mActions.push_back(newBox);
}

bool ActionTab::hasSelection() const {
    return mSelectedAction != -1;
}

void ActionTab::select(unsigned index) {
    if (hasSelection()) {
        mActions[mSelectedAction].deactivate();
    }
    mSelectedAction = index;
    mActions[mSelectedAction].activate();
}

void ActionTab::resetSelection() {
    mSelectedAction = -1;
}

#include "ActionTab.h"

#include <cassert>
#include <iostream>

ActionTab::ActionTab() {
    mRect = {985, 181, 455, 436};
    mColor = AppColor::BACKGROUND_4;

    mSubmitButton.setRect({1131, 555, 166, 46});
    mSubmitButton.setColor(AppColor::PRIMARY);
    mSubmitButton.setContentColor(AppColor::TEXT_ACCENT);
    mSubmitButton.setText("Simulate");
    mSubmitButton.setTextSize(25);
    mSubmitButton.deactivate();

    setSubmitCallback();
}

void ActionTab::update(float dt) {
    if (!mIsActivated)
        return;
    for (auto &action : mActions) {
        action.update(dt);
    }
    mSubmitButton.update(dt);
}

void ActionTab::draw() {
    if (!mIsActivated)
        return;
    DrawRectangleRec(mRect, mColor);
    for (auto &action : mActions) {
        action.draw();
    }
    mSubmitButton.draw();
}

void ActionTab::addActionSelector(
    std::string title, std::vector<ActionBox::Input> inputs,
    std::function<void(ActionBox::InputData, bool)> onSubmit) {
    mOnSubmits.push_back(onSubmit);

    const int curIndex = mActions.size();

    auto onSelect = [this, curIndex]() {
        this->select(curIndex);
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    };

    int startingY;
    if (mActions.empty()) {
        startingY = 200;
    } else {
        startingY = mActions.back().getPosition().y + 87;
    }

    ActionBox newBox = ActionBox((Rectangle){1020, startingY, 385, 77}, title,
                                 inputs, onSelect);

    mActions.push_back(newBox);
}

void ActionTab::activate() {
    mIsActivated = true;
}

void ActionTab::deactivate() {
    mIsActivated = false;
    resetSelection();
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
    mSubmitButton.activate();
}

void ActionTab::resetSelection() {
    if (hasSelection())
        mActions[mSelectedAction].deactivate();
    mSelectedAction = -1;
    mSubmitButton.deactivate();
}

void ActionTab::setSubmitCallback() {
    mSubmitButton.setCallback([this]() {
        assert(hasSelection());
        int idx = this->mSelectedAction;
        auto getInputStatus = this->mActions[idx].getInputs();
        this->mOnSubmits[idx](getInputStatus.second, getInputStatus.first);
    });
}

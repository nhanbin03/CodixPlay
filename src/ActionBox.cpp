#include "ActionBox.h"

#include "Helper.h"

ActionBox::ActionBox(
    std::string title, std::vector<Input> inputs,
    std::function<void(std::map<std::string, std::string>)> onSubmit,
    std::function<void()> onSelect)
: mTitle(title)
, mInputs(inputs)
, mOnSubmit(onSubmit)
, mOnSelect(onSelect) {
    mSelectButton.setCallback(onSelect);
    mSelectButton.setText(title);

    mColor = AppColor::BACKGROUND_4;
    mBorderColor = AppColor::BACKGROUND_2;
    mBorderThickness = 2;

    mTextColor = AppColor::TEXT;
}

void ActionBox::update(float dt) {
    if (mIsActivated) {
        activeUpdate(dt);
    } else {
        inactiveUpdate(dt);
    }
}

void ActionBox::draw() {
    if (mIsActivated) {
        activeDraw();
    } else {
        inactiveDraw();
    }
}

void ActionBox::activeUpdate(float dt) {
    for (auto& input : mInputBoxes) {
        input.update(dt);
    }
}

void ActionBox::inactiveUpdate(float dt) {
    mSelectButton.setRect(mRect);
    mSelectButton.update(dt);
}

void ActionBox::activeDraw() {
    DrawRectangleRounded(mRect, 0.5, 100, mColor);
    DrawRectangleRoundedLines(mRect, 0.5, 100, mBorderThickness, mBorderColor);

    int textSize = 19;
    const Font& font =
        FontHolder::getInstance().get(FontID::Inter_Bold, textSize);
    DrawTextEx(font, mTitle.c_str(), getPosition() + (Vector2){23, 10},
               textSize, 0, mTextColor);
}

void ActionBox::inactiveDraw() {
    mSelectButton.draw();
}

void ActionBox::activate() {
    mIsActivated = true;
}

void ActionBox::deactivate() {
    mIsActivated = false;
}

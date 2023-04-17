#include "ActionBox.h"

#include "Helper.h"

#include <iostream>

ActionBox::ActionBox(Rectangle bounds, std::string title,
                     std::vector<Input> inputs, std::function<void()> onSelect)
: mTitle(title)
, mInputs(inputs)
, mOnSelect(onSelect) {
    mRect = bounds;

    mSelectButton.setCallback(onSelect);
    mSelectButton.setText(title);
    mSelectButton.setColor(AppColor::BACKGROUND_4);
    mSelectButton.setBorderColor(AppColor::BACKGROUND_2);
    mSelectButton.setBorderThickness(2);
    mSelectButton.setContentColor(AppColor::TEXT);
    mSelectButton.setTextSize(25);

    mColor = AppColor::BACKGROUND_4;
    mBorderColor = AppColor::BACKGROUND_2;
    mBorderThickness = 2;
    mTextColor = AppColor::TEXT;

    for (auto& input : mInputs) {
        InputBox newBox;

        int startingX;
        if (mInputBoxes.empty()) {
            startingX = mRect.x + 50;
        } else {
            startingX = mInputBoxes.back().getPosition().x
                      + mInputBoxes.back().getSize().x + 50;
        }
        Vector2 labelBounds = MeasureTextEx(
            FontHolder::getInstance().get(FontID::Consolas, INPUT_LABEL_SIZE),
            input.label.c_str(), INPUT_LABEL_SIZE, 0);

        newBox.setRect((Rectangle){startingX + labelBounds.x, mRect.y + 45,
                                   input.width, 24});
        newBox.setColor(AppColor::TEXT);
        newBox.setBorderColor(AppColor::BACKGROUND_1);
        newBox.setBorderThickness(1);

        mInputBoxes.push_back(newBox);
    }
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
    DrawRectangleRounded(mRect, 0.5, ROUNDED_SEGMENTS, mColor);
    DrawRectangleRoundedLines(mRect, 0.5, ROUNDED_SEGMENTS, mBorderThickness,
                              mBorderColor);

    int textSize = 19;
    const Font& font =
        FontHolder::getInstance().get(FontID::Inter_Bold, textSize);
    DrawTextEx(font, mTitle.c_str(), getPosition() + (Vector2){23, 10},
               textSize, 0, mTextColor);
    DrawRectangleRounded({mRect.x + 6, mRect.y + 18, 4, 41}, 1,
                         ROUNDED_SEGMENTS,
                         AppColor::PRIMARY); // Draw active indicator

    for (int i = 0; i < mInputs.size(); i++) {
        int startingX;
        if (i == 0) {
            startingX = mRect.x + 50;
        } else {
            startingX = mInputBoxes[i - 1].getPosition().x
                      + mInputBoxes[i - 1].getSize().x + 50;
        }

        const Font& font =
            FontHolder::getInstance().get(FontID::Consolas, INPUT_LABEL_SIZE);
        DrawTextEx(font, mInputs[i].label.c_str(),
                   (Vector2){startingX, mRect.y + 48}, INPUT_LABEL_SIZE, 0,
                   AppColor::TEXT);

        mInputBoxes[i].draw();
    }
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

std::pair<bool, ActionBox::InputData> ActionBox::getInputs() const {
    InputData ret;
    for (int i = 0; i < mInputs.size(); i++) {
        std::string inputString = mInputBoxes[i].getInputText();
        if (mInputs[i].validator(inputString) == false) {
            return {false, InputData()};
        }
        ret[mInputs[i].name] = inputString;
    }
    return {true, ret};
}

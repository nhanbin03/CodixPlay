#include "NumberInputBox.h"

#include <iostream>

NumberInputBox::NumberInputBox(Rectangle bounds) {
    mRect = bounds;
    mColor = WHITE;
    mBorderColor = BLACK;
    mBorderThickness = 1;
}

NumberInputBox::~NumberInputBox() {
}

void NumberInputBox::update(float dt) {
    checkInteraction();

    if (mIsFocused) {
        int key = GetCharPressed();
        while (key > 0) {
            if (isValid(key) && (mInputText.size() < MAX_TEXT_LENGTH)) {
                mInputText.push_back(key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && mInputText.size() > 0) {
            mInputText.pop_back();
        }
    }
}

void NumberInputBox::draw() {
    DrawRectangleRec(mRect, mColor);
    if (mBorderThickness != 0)
        DrawRectangleLinesEx(mRect, mBorderThickness, mBorderColor);

    int textSize = mRect.height * 2 / 3;
    std::string displayText = mInputText;
    if (mIsFocused)
        displayText += '_';
    Vector2 textBounds =
        MeasureTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                      displayText.c_str(), textSize, 0);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
               displayText.c_str(),
               {mRect.x + mRect.width / 2 - textBounds.x / 2,
                mRect.y + mRect.height / 2 - textBounds.y / 2},
               textSize, 0, mTextColor);
}

std::string NumberInputBox::getInputText() {
    return mInputText;
}

void NumberInputBox::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, mRect)) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mIsFocused = true;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mIsFocused = false;
        }
    }
}

bool NumberInputBox::isValid(int key) {
    if (!('0' <= key && key <= '9'))
        return false;
    if (mInputText.size() == 0 && key == '0')
        return false;
    return true;
}

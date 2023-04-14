#include "NumberInputBox.h"

#include <iostream>

NumberInputBox::NumberInputBox() {
}

NumberInputBox::NumberInputBox(Rectangle bounds) {
    setRect(bounds);
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
    DrawRectangleRec(getRect(), mColor);
    DrawRectangleLinesEx(getRect(), mBorderThickness, mBorderColor);

    int textSize = getRect().height * 2 / 3;
    std::string displayText = mInputText;
    if (mIsFocused)
        displayText += '_';
    DrawText(displayText.c_str(),
             getRect().x + getRect().width / 2
                 - MeasureText(displayText.c_str(), textSize) / 2,
             getRect().y + getRect().height / 2 - textSize / 2, textSize,
             mTextColor);
}

std::string NumberInputBox::getInputText() {
    return mInputText;
}

void NumberInputBox::setBorderThickness(int thickness) {
    mBorderThickness = thickness;
}

void NumberInputBox::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, getRect())) {
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

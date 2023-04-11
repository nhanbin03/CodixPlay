#include "NumberInputBox.h"

#include <iostream>

NumberInputBox::NumberInputBox() {
}

NumberInputBox::NumberInputBox(Rectangle bounds)
: mBounds(bounds) {
    setPosition({bounds.x, bounds.y});
    setSize({bounds.width, bounds.height});
}

NumberInputBox::~NumberInputBox() {
}

void NumberInputBox::update(float dt) {
    mBounds = {getPosition().x, getPosition().y, getSize().x, getSize().y};

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
    DrawRectangleRec(mBounds, mColor);
    DrawRectangleLinesEx(mBounds, mBorderThickness, mBorderColor);

    int textSize = mBounds.height * 2 / 3;
    std::string displayText = mInputText;
    if (mIsFocused)
        displayText += '_';
    DrawText(displayText.c_str(),
             mBounds.x + mBounds.width / 2
                 - MeasureText(displayText.c_str(), textSize) / 2,
             mBounds.y + mBounds.height / 2 - textSize / 2, textSize,
             mTextColor);
}

void NumberInputBox::setPosition(Vector2 position) {
    GUIComponent::setPosition(position);
    mBounds.x = position.x;
    mBounds.y = position.y;
}

void NumberInputBox::setSize(Vector2 size) {
    GUIComponent::setSize(size);
    mBounds.width = size.x;
    mBounds.height = size.y;
}

std::string NumberInputBox::getInputText() {
    return mInputText;
}

void NumberInputBox::setBorderThickness(int thickness) {
    mBorderThickness = thickness;
}

void NumberInputBox::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, mBounds)) {
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

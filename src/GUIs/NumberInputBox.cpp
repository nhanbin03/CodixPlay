#include "NumberInputBox.h"

#include <iostream>

NumberInputBox::NumberInputBox(Rectangle bounds)
: mBounds(bounds)
, mColor(WHITE)
, mBorderColor(BLACK)
, mTextColor(BLACK)
, mIsFocused(false)
, mBorderThickness(1) {
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
        std::cout << char(key) << "\n";
        while (key > 0) {
            if (isValid(key) && (mInputText.size() < MAX_LEN)) {
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
    if (mIsFocused) displayText += '_';
    DrawText(displayText.c_str(), mBounds.x + mBounds.width / 2 - MeasureText(displayText.c_str(), textSize) / 2,
             mBounds.y + mBounds.height / 2 - textSize / 2, textSize, mTextColor);
}

std::string NumberInputBox::getInputText() {
    return mInputText;
}

void NumberInputBox::setBorderThickness(int thickness) {
    mBorderThickness = thickness;
}

void NumberInputBox::checkInteraction()
{
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
    if (!('0' <= key && key <= '9')) return false;
    if (mInputText.size() == 0 && key == '0') return false;
    return true;
}

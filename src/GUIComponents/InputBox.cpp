#include "InputBox.h"

InputBox::InputBox(Rectangle bounds) {
    mRect = bounds;
    mColor = WHITE;
    mBorderColor = BLACK;
    mBorderThickness = 1;
}

InputBox::~InputBox() {
}

void InputBox::update(float dt) {
    checkInteraction();

    if (mIsFocused) {
        int key = GetCharPressed();
        while (key > 0) {
            mInputText.push_back(key);
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && mInputText.size() > 0) {
            mInputText.pop_back();
        }
    }
}

void InputBox::draw() {
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

std::string InputBox::getInputText() {
    return mInputText;
}

void InputBox::checkInteraction() {
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

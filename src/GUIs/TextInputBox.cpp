#include "TextInputBox.h"

TextInputBox::TextInputBox(Rectangle bounds)
: mBounds(bounds)
, mColor(WHITE)
, mBorderColor(BLACK)
, mTextColor(BLACK)
, mIsFocused(false) {
    setPosition({bounds.width, bounds.height});
    setSize({bounds.x, bounds.y});
}

TextInputBox::~TextInputBox() {
}

void TextInputBox::update(float dt) {
    mBounds = {getPosition().x, getPosition().y, getSize().x, getSize().y};

    checkInteraction();

    if (mIsFocused) {
        int key = GetCharPressed();

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

void TextInputBox::draw() {
    DrawRectangleRec(mBounds, mColor);
    DrawRectangleLinesEx(mBounds, mBorderThickness, mBorderColor);
}

void TextInputBox::checkInteraction() {
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

bool TextInputBox::isValid(int key) {
    if (!('0' <= key && key <= '9')) return false;
    if (mInputText.size() == 0 && key == '0') return false;
    return true;
}

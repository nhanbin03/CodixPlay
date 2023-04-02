#include "Button.h"

Button::Button(Rectangle rec)
: mState(ButtonState::None),
mButton(rec),
mColor(BLACK),
mTextColor(WHITE) {
    setPosition({rec.x, rec.y});
    setSize({rec.width, rec.height});
}

Button::~Button() {
}

void Button::update(float dt) {
    mButton = {getPosition().x, getPosition().y, getSize().x, getSize().y};

    checkInteraction();
}


void Button::draw() {
    DrawRectangleRec(mButton, mColor);
    DrawText(mText.c_str(), mButton.x + mButton.width / 2 - MeasureText(mText.c_str(), mTextSize) / 2,
                    mButton.y + mButton.height / 2 - mTextSize / 2, mTextSize, mTextColor);
}

void Button::setCallback(Callback callback) {
    mCallback = callback;
}

void Button::setText(const std::string text) {
    mText = text;
}

void Button::setTextSize(int size) {
    mTextSize = 30;
}

void Button::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, mButton)) {
        
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

        if (mState == ButtonState::None)
            mState = ButtonState::Focused;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mState = ButtonState::Active;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mState == ButtonState::Active) {
            mState = ButtonState::None;
            mCallback();
        }
    } else {
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) || mState != ButtonState::Active) {
            mState = ButtonState::None;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
}

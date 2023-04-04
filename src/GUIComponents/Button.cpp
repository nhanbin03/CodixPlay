#include "Button.h"

Button::Button(Rectangle bounds)
: mButton(bounds)
, mState(ButtonState::None)
, mColor(BLACK)
, mTextColor(WHITE) {
    setPosition({bounds.x, bounds.y});
    setSize({bounds.width, bounds.height});
}

Button::~Button() {
}

void Button::update(float dt) {
    checkInteraction();
}

void Button::draw() {
    DrawRectangleRec(mButton, mColor);
    DrawText(mText.c_str(),
             mButton.x + mButton.width / 2
                 - MeasureText(mText.c_str(), mTextSize) / 2,
             mButton.y + mButton.height / 2 - mTextSize / 2, mTextSize,
             mTextColor);
}

void Button::setPosition(Vector2 position) {
    GUIComponent::setPosition(position);
    mButton.x = position.x;
    mButton.y = position.y;
}

void Button::setSize(Vector2 size) {
    GUIComponent::setSize(size);
    mButton.width = size.x;
    mButton.height = size.y;
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
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
            && mState == ButtonState::Active) {
            mState = ButtonState::None;
            mCallback();
        }
    } else {
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)
            || mState != ButtonState::Active) {
            mState = ButtonState::None;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    }
}

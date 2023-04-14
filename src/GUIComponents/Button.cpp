#include "Button.h"

Button::Button(Rectangle bounds)
: mButton(bounds) {
    setPosition({bounds.x, bounds.y});
    setSize({bounds.width, bounds.height});
}

Button::~Button() {
}

void Button::update(float dt) {
    checkInteraction();
}

void Button::draw() {
    float filterBrightness = 0;
    if (mState != ButtonState::None) {
        int r = mColor.r;
        int g = mColor.g;
        int b = mColor.b;
        float luminance = (0.2126 * r + 0.7152 * g + 0.0722 * b);
        if (luminance < 128) // Test if the color is dark
            filterBrightness = 0.2;
        else
            filterBrightness = -0.2;
    }
    DrawRectangleRounded(mButton, 0.5, SEGMENTS,
                         ColorBrightness(mColor, filterBrightness));
    if (mBorderThickness != 0) {
        DrawRectangleRoundedLines(
            mButton, 0.5, SEGMENTS, mBorderThickness,
            ColorBrightness(mBorderColor, filterBrightness));
    }
    if (mTextSize == 0) {
        mTextSize = mButton.height / 2;
    }
    DrawText(mText.c_str(),
             mButton.x + mButton.width / 2
                 - MeasureText(mText.c_str(), mTextSize) / 2,
             mButton.y + mButton.height / 2 - mTextSize / 2, mTextSize,
             ColorBrightness(mTextColor, filterBrightness));
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

void Button::setColor(Color color) {
    mColor = color;
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

void Button::setTextColor(Color color) {
    mTextColor = color;
}

void Button::setBorderThickness(int thickness) {
    mBorderThickness = thickness;
}

void Button::setBorderColor(Color color) {
    mBorderColor = color;
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
        if (!(IsMouseButtonDown(MOUSE_BUTTON_LEFT)
              && mState == ButtonState::Active)) {
            if (mState == ButtonState::Focused || mState == ButtonState::Active)
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            mState = ButtonState::None;
        }
    }
}

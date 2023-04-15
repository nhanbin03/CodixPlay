#include "Button.h"

#include "../Helper.h"

Button::Button(Rectangle bounds) {
    mRect = bounds;
    mColor = GRAY;
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
    DrawRectangleRounded(mRect, 0.5, SEGMENTS,
                         ColorBrightness(mColor, filterBrightness));

    if (mBorderThickness != 0) {
        DrawRectangleRoundedLines(
            mRect, 0.5, SEGMENTS, mBorderThickness,
            ColorBrightness(mBorderColor, filterBrightness));
    }

    if (mTextSize == 0) {
        mTextSize = mRect.height / 2;
    }
    DrawText(
        mText.c_str(),
        mRect.x + mRect.width / 2 - MeasureText(mText.c_str(), mTextSize) / 2,
        mRect.y + mRect.height / 2 - mTextSize / 2, mTextSize,
        ColorBrightness(mTextColor, filterBrightness));

    DrawTextureV(mTexture, getPosition(), WHITE);
}

void Button::setSize(Vector2 size) {
    GUIComponent::setSize(size);
    scaleTexture(mTexture, getSize());
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

void Button::setTexture(Texture2D texture) {
    mTexture = texture;
    scaleTexture(mTexture, getSize());
}

void Button::checkInteraction() {
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, mRect)) {
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

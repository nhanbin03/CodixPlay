#include "Button.h"

#include "../Helper.h"

#include <iostream>

Button::Button(Rectangle bounds) {
    mRect = bounds;
    mColor = GRAY;

    mInactivatedFilter = [](Color color) {
        int r = color.r;
        int g = color.g;
        int b = color.b;
        float luminance =
            0.2126 * r + 0.7125 * g + 0.0722 * b; // Grayscaling from wiki
        color.r = luminance;
        color.g = luminance;
        color.b = luminance;
        return color;
    };
}

Button::~Button() {
}

void Button::update(float dt) {
    if (mIsActivated)
        checkInteraction();
}

void Button::draw() {
    float filterBrightness = 0;
    if (mState != ButtonState::None) {
        // int r = mColor.r;
        // int g = mColor.g;
        // int b = mColor.b;
        // float luminance = (0.2126 * r + 0.7152 * g + 0.0722 * b);
        // if (luminance < 128) // Test if the color is dark
        //     filterBrightness = 0.2;
        // else
        //     filterBrightness = -0.2;
        filterBrightness = -0.2;
    }

    Filter colorFilter;
    if (mIsActivated) {
        colorFilter = [filterBrightness](Color color) {
            return ColorBrightness(color, filterBrightness);
        };
    } else {
        colorFilter = mInactivatedFilter;
    }

    DrawRectangleRounded(mRect, mCornerRoundness, ROUNDED_SEGMENTS,
                         colorFilter(mColor));

    if (mBorderThickness != 0) {
        DrawRectangleRoundedLines(mRect, mCornerRoundness, ROUNDED_SEGMENTS,
                                  mBorderThickness, colorFilter(mBorderColor));
    }

    if (mTextSize == 0) {
        mTextSize = mRect.height / 2;
    }
    Vector2 textBounds = MeasureTextEx(
        FontHolder::getInstance().get(FontID::Inter_Bold, mTextSize),
        mText.c_str(), mTextSize, 0);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, mTextSize),
               mText.c_str(),
               {mRect.x + mRect.width / 2 - textBounds.x / 2,
                mRect.y + mRect.height / 2 - textBounds.y / 2},
               mTextSize, 0, colorFilter(mContentColor));

    if (mHasTexture)
        DrawTextureV(mTexture, getPosition(), colorFilter(mContentColor));
}

void Button::setSize(Vector2 size) {
    GUIComponent::setSize(size);
    if (mHasTexture)
        scaleTexture(mTexture, getSize());
}

void Button::setCallback(Callback callback) {
    mCallback = callback;
}

void Button::triggerCallback() {
    mCallback();
}

void Button::setText(const std::string text) {
    mText = text;
}

void Button::setTextSize(int size) {
    mTextSize = size;
}

void Button::setContentColor(Color color) {
    mContentColor = color;
}

void Button::setTexture(Texture2D texture) {
    mHasTexture = true;
    mTexture = texture;
    scaleTexture(mTexture, getSize());
}

Color Button::getColor() const {
    return mColor;
}

void Button::setCornerRoundness(float cornerRoundness) {
    mCornerRoundness = cornerRoundness;
}

void Button::setInactivatedFilter(Filter filter) {
    mInactivatedFilter = filter;
}

void Button::activate() {
    mIsActivated = true;
}

void Button::deactivate() {
    if (mIsActivated)
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    mIsActivated = false;
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

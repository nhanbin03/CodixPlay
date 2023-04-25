#include "SquareNode.h"

#include <cassert>
#include <iostream>

SquareNode::SquareNode() {
    setTransparency(NO_VALUE_ALPHA);
}

SquareNode::~SquareNode() {
}

void SquareNode::draw() {
    int x = getPosition().x;
    int y = getPosition().y;

    float displaySize = mSize * getScale();
    float displayBorder = BORDER_THICKNESS * getScale();

    auto mColorFilter = [this](Color color) {
        return ColorAlpha(color, this->mTransparency);
    };

    DrawRectangle(x, y, displaySize, displaySize, mColorFilter(mColor));
    DrawRectangleLinesEx((Rectangle){x, y, displaySize, displaySize},
                         displayBorder,
                         mColorFilter(mBorderColor)); // Draw border inside

    if (mHasValue) {
        const char *valueText = std::to_string(mValue).c_str();
        float textSize = displaySize / 2;
        Vector2 textBounds = MeasureTextEx(
            FontHolder::getInstance().get(FontID::Inter_Bold, textSize),
            valueText, textSize, 0);
        DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, textSize),
                   valueText,
                   {x + displaySize / 2 - textBounds.x / 2,
                    y + displaySize / 2 - textBounds.y / 2},
                   textSize, 0, mColorFilter(mValueColor));
    }
}

void SquareNode::setValue(int value) {
    mHasValue = true;
    mValue = value;
    setTransparency(1);
}

int SquareNode::getValue() const {
    assert(mHasValue);
    return mValue;
}

void SquareNode::removeValue() {
    mHasValue = false;
    setTransparency(NO_VALUE_ALPHA);
}

bool SquareNode::hasValue() const {
    return mHasValue;
}

void SquareNode::setValueColor(Color color) {
    mValueColor = color;
}

Color SquareNode::getValueColor() const {
    return mValueColor;
}

void SquareNode::setColor(Color color) {
    mColor = color;
}

Color SquareNode::getColor() const {
    return mColor;
}

void SquareNode::setBorderColor(Color color) {
    mBorderColor = color;
}

Color SquareNode::getBorderColor() const {
    return mBorderColor;
}

void SquareNode::setTransparency(float alpha) {
    if (alpha < 0 || alpha > 1)
        return;
    mTransparency = alpha;
}

float SquareNode::getTransparency() const {
    return mTransparency;
}

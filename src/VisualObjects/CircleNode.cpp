#include "CircleNode.h"

CircleNode::CircleNode() {
}

CircleNode::~CircleNode() {
}

void CircleNode::draw() {
    int x = getPosition().x;
    int y = getPosition().y;

    float displayRadius = mRadius * getScale();
    float displayBorder = BORDER_THICKNESS * getScale();

    DrawCircle(x, y, displayRadius, mColor);
    DrawRectangleRoundedLines(
        {x - displayRadius + displayBorder, y - displayRadius + displayBorder,
         (displayRadius - displayBorder) * 2,
         (displayRadius - displayBorder) * 2},
        1, ROUNDED_SEGMENTS, displayBorder, mBorderColor); // Draw border inside

    const char *valueText = std::to_string(mValue).c_str();
    float textSize = displayRadius;
    Vector2 textBounds = MeasureTextEx(
        FontHolder::getInstance().get(FontID::Inter_Bold, textSize), valueText,
        textSize, 0);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, textSize),
               valueText, {x - textBounds.x / 2, y - textBounds.y / 2},
               textSize, 0, mValueColor);
}

void CircleNode::setValue(int value) {
    mValue = value;
}

int CircleNode::getValue() const {
    return mValue;
}

void CircleNode::setValueColor(Color color) {
    mValueColor = color;
}

Color CircleNode::getValueColor() const {
    return mValueColor;
}

void CircleNode::setColor(Color color) {
    mColor = color;
}

Color CircleNode::getColor() const {
    return mColor;
}

void CircleNode::setBorderColor(Color color) {
    mBorderColor = color;
}

Color CircleNode::getBorderColor() const {
    return mBorderColor;
}

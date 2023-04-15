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
        1, 100, displayBorder, mBorderColor);

    const char *valueText = std::to_string(mValue).c_str();
    float fontSize = displayRadius - displayBorder;
    DrawText(valueText, x - MeasureText(valueText, fontSize) / 2,
             y - fontSize / 2, fontSize, mValueColor);
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

#include "CircleNode.h"

CircleNode::CircleNode() {
}

CircleNode::~CircleNode() {
}

void CircleNode::draw() {
    int x = getPosition().x;
    int y = getPosition().y;

    DrawCircle(x, y, mRadius * getScale(), mColor);

    const char *valueText = std::to_string(mValue).c_str();
    float fontSize = mRadius * getScale();
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

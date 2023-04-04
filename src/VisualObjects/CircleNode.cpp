#include "CircleNode.h"

CircleNode::CircleNode()
: mRadius(ELEMENT_SIZE / 2)
, mColor(BLACK)
, mValue(0)
, mValueColor(WHITE) {
    
}

CircleNode::~CircleNode() {
}

void CircleNode::draw() {
    int x = getPosition().x;
    int y = getPosition().y;

    DrawCircle(x, y, mRadius * getScale(), mColor);

    const char *valueText = std::to_string(mValue).c_str();
    int fontSize = ELEMENT_SIZE / 2;
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

void CircleNode::setColor(Color color) {
    mColor = color;
}

#include "SquareNode.h"

SquareNode::SquareNode() {
}

SquareNode::~SquareNode() {
}

void SquareNode::draw() {
    int x = getPosition().x;
    int y = getPosition().y;

    float displaySize = mSize * getScale();
    float displayBorder = BORDER_THICKNESS * getScale();

    DrawRectangle(x, y, displaySize, displaySize, mColor);
    DrawRectangleLinesEx((Rectangle){x, y, displaySize, displaySize},
                         displayBorder,
                         mBorderColor); // Draw border inside

    const char *valueText = std::to_string(mValue).c_str();
    float textSize = displaySize / 2;
    Vector2 textBounds = MeasureTextEx(
        FontHolder::getInstance().get(FontID::Inter_Bold, textSize), valueText,
        textSize, 0);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, textSize),
               valueText,
               {x + displaySize / 2 - textBounds.x / 2,
                y + displaySize / 2 - textBounds.y / 2},
               textSize, 0, mValueColor);
}

void SquareNode::setValue(int value) {
    mValue = value;
}

int SquareNode::getValue() const {
    return mValue;
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

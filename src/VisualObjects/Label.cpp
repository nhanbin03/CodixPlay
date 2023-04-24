#include "Label.h"

Label::Label(std::string text)
: mText(text) {
}

Label::~Label() {
}

void Label::draw() {
    int textSize = mSize;
    Vector2 textBounds = MeasureTextEx(
        FontHolder::getInstance().get(FontID::Inter_Bold, textSize),
        mText.c_str(), textSize, 0);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, textSize),
               mText.c_str(),
               {getPosition().x - textBounds.x / 2,
                getPosition().y - textBounds.y / 2},
               textSize, 0, mColor);
}

void Label::setText(std::string text) {
    mText = text;
}

void Label::setColor(Color color) {
    mColor = color;
}

void Label::setSize(int size) {
    mSize = size;
}

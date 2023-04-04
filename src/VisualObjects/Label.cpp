#include "Label.h"

Label::Label(std::string text)
: mText(text) {
}

Label::~Label() {
}

void Label::draw() {
    DrawText(mText.c_str(),
             getPosition().x - MeasureText(mText.c_str(), mSize) / 2,
             getPosition().y - mSize / 2, mSize, mColor);
}

void Label::setText(std::string text) {
    mText = text;
}

void Label::setColor(Color color) {
    mColor = color;
}
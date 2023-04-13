#include "Label.h"

Label::Label(std::string text)
: mText(text) {
}

Label::~Label() {
}

void Label::draw() {
    int fontSize = mSize;
    DrawText(mText.c_str(),
             getPosition().x - MeasureText(mText.c_str(), fontSize) / 2,
             getPosition().y - fontSize / 2, fontSize, mColor);
}

void Label::setText(std::string text) {
    mText = text;
}

void Label::setColor(Color color) {
    mColor = color;
}
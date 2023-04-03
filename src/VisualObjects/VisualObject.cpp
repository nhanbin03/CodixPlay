#include "VisualObject.h"

VisualObject::VisualObject()
: mScale(1) {
}

VisualObject::~VisualObject() {
}

void VisualObject::setPosition(Vector2 position) {
    mPosition = position;
}

Vector2 VisualObject::getPosition() {
    return mPosition;
}

void VisualObject::setScale(float scale)  {
    mScale = scale;
}

float VisualObject::getScale() {
    return mScale;
}

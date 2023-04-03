#include "VisualObject.h"

VisualObject::VisualObject() {
}

VisualObject::~VisualObject() {
}

void VisualObject::setPosition(Vector2 position) {
    mPosition = position;
}

Vector2 VisualObject::getPosition() {
    return mPosition;
}

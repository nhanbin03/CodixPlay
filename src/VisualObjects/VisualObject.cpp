#include "VisualObject.h"

int VisualObject::objectIDTracker = 0;

VisualObject::VisualObject() {
    objectIDTracker++;
}

VisualObject::~VisualObject() {
}

void VisualObject::setPosition(Vector2 position) {
    mPosition = position;
}

Vector2 VisualObject::getPosition() const {
    return mPosition;
}

void VisualObject::setScale(float scale) {
    mScale = scale;
}

float VisualObject::getScale() const {
    return mScale;
}

void VisualObject::setZIndex(int zIndex) {
    mZIndex = zIndex;
}

int VisualObject::getZIndex() const {
    return mZIndex;
}

int VisualObject::getObjectID() const {
    return objectIDTracker;
}

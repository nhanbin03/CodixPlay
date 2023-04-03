#include "GUIComponent.h"

GUIComponent::GUIComponent() {
}

GUIComponent::~GUIComponent() {
}

Vector2 GUIComponent::getPosition() const {
    return mPosition;
}

void GUIComponent::setPosition(Vector2 position) {
    mPosition = position;
}

Vector2 GUIComponent::getSize() const {
    return mSize;
}

void GUIComponent::setSize(Vector2 size) {
    mSize = size;
}

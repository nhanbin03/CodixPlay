#include "Arrow.h"

#include <math.h>
#include <cassert>
#include <iostream>

#include "../Helper.h"

Arrow::Arrow() {
}

Arrow::~Arrow() {
}

void Arrow::draw() {
    // Draw arrow head
    Vector2 scaledDestination = mSource + (mDestination - mSource) * getScale();

    int x = scaledDestination.x - mSource.x;
    int y = scaledDestination.y - mSource.y;
    if (x * x + y * y <= ELEMENT_SIZE * ELEMENT_SIZE)
        return;
    Vector2 unitVector = {mThickness * x / sqrt(x * x + y * y),
                          mThickness * y / sqrt(x * x + y * y)};
    if (x < unitVector.x && y < unitVector.y)
        return;

    Vector2 inverseVector = {unitVector.y, -unitVector.x};

    Vector2 headDestination = {
        scaledDestination.x - unitVector.x * ELEMENT_SIZE / mThickness / 2,
        scaledDestination.y - unitVector.y * ELEMENT_SIZE / mThickness / 2};

    Vector2 arrowPoint = headDestination;
    Vector2 arrowSide1 = {
        headDestination.x - 2 * unitVector.x + inverseVector.x,
        headDestination.y - 2 * unitVector.y + inverseVector.y};
    Vector2 arrowSide2 = {
        headDestination.x - 2 * unitVector.x - inverseVector.x,
        headDestination.y - 2 * unitVector.y - inverseVector.y};

    DrawTriangle(arrowPoint, arrowSide1, arrowSide2, mColor);

    // Draw arrow line
    DrawLineEx(
        mSource,
        {headDestination.x - unitVector.x, headDestination.y - unitVector.y},
        mThickness, mColor);
}

void Arrow::setSource(Vector2 position) {
    mSource = position;
}

Vector2 Arrow::getSource() const {
    return mSource;
}

void Arrow::setDestination(Vector2 position) {
    mDestination = position;
}

Vector2 Arrow::getDestination() const {
    return mDestination;
}

void Arrow::setThickness(int thickness) {
    mThickness = thickness;
}

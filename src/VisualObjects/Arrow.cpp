#include "Arrow.h"

#include <math.h>

Arrow::Arrow() {
}

Arrow::~Arrow() {
}

void Arrow::draw() {
    // Draw arrow head
    int x = mDestination.x - mSource.x;
    int y = mDestination.y - mSource.y;
    Vector2 unitVector = {mThickness * x / sqrt(x * x + y * y),
                          mThickness * y / sqrt(x * x + y * y)};
    Vector2 inverseVector = {unitVector.y, -unitVector.x};

    Vector2 arrowPoint = mDestination;

    Vector2 arrowSide1 = {mDestination.x - 2 * unitVector.x + inverseVector.x,
                          mDestination.y - 2 * unitVector.y + inverseVector.y};

    Vector2 arrowSide2 = {mDestination.x - 2 * unitVector.x - inverseVector.x,
                          mDestination.y - 2 * unitVector.y - inverseVector.y};

    DrawTriangle(arrowPoint, arrowSide1, arrowSide2, mColor);

    // Draw arrow line
    DrawLineEx(mSource,
               {mDestination.x - unitVector.x, mDestination.y - unitVector.y},
               mThickness, mColor);
}

void Arrow::setSource(Vector2 position) {
    mSource = position;
}

void Arrow::setDestination(Vector2 position) {
    mDestination = position;
}

void Arrow::setThickness(int thickness) {
    mThickness = thickness;
}

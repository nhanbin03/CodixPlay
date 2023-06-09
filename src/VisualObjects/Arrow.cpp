#include "Arrow.h"

#include <math.h>
#include <cassert>
#include <iostream>

#include "../Helper.h"

Arrow::Arrow(bool isCircular) {
    mIsCircular = isCircular;
}

Arrow::~Arrow() {
}

void Arrow::draw() {
    if (mIsCircular)
        circularDraw();
    else
        regularDraw();
}

void Arrow::regularDraw() {
    drawArrow(
        mSource, mDestination, getScale(),
        sqrt(ELEMENT_SIZE * ELEMENT_SIZE / 4.0 - mSideOffset * mSideOffset));
}

// ___________
// |   (3)    |
// |(4)       |(2)
// v       (1)|
// O     O-----
void Arrow::circularDraw() {
    const float TAIL_LENGTH = 50;
    const float HEIGHT = 200;

    float lengthOne = TAIL_LENGTH;
    Vector2 posOneTwo = mSource + (Vector2){TAIL_LENGTH, 0};

    float lengthTwo = lengthOne + HEIGHT;
    Vector2 posTwoThree = mSource + (Vector2){TAIL_LENGTH, -HEIGHT};

    float lengthThree = lengthTwo + mSource.x + TAIL_LENGTH - mDestination.x;
    Vector2 posThreeFour = mDestination + (Vector2){0, -HEIGHT};

    float lengthFour = lengthThree + HEIGHT;

    float curLength = lengthFour * getScale();

    // Draw straight line
    if (curLength > lengthOne) {
        drawLine(mSource, posOneTwo);
    }
    if (curLength > lengthTwo) {
        drawLine(posOneTwo, posTwoThree);
    }
    if (curLength > lengthThree) {
        drawLine(posTwoThree, posThreeFour);
    }

    // Draw arrow
    if (curLength <= lengthOne) {
        drawArrow(mSource, posOneTwo, curLength / lengthOne);
    } else if (curLength <= lengthTwo) {
        drawArrow(posOneTwo, posTwoThree,
                  (curLength - lengthOne) / (lengthTwo - lengthOne));
    } else if (curLength <= lengthThree) {
        drawArrow(posTwoThree, posThreeFour,
                  (curLength - lengthTwo) / (lengthThree - lengthTwo));
    } else {
        drawArrow(posThreeFour, mDestination,
                  (curLength - lengthThree) / (lengthFour - lengthThree),
                  ELEMENT_SIZE / 2.0);
    }
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

void Arrow::setCircular(bool isCircular) {
    mIsCircular = isCircular;
}

bool Arrow::isCircular() const {
    return mIsCircular;
}

void Arrow::setSideOffset(int sideOffset) {
    mSideOffset = sideOffset;
}

int Arrow::getSideOffset() const {
    return mSideOffset;
}

void Arrow::drawArrow(Vector2 source, Vector2 destination, float scale,
                      float headOffset) {
    Vector2 scaledDestination = source + (destination - source) * scale;

    float x = scaledDestination.x - source.x;
    float y = scaledDestination.y - source.y;
    if (x * x + y * y <= 2 * mThickness * 2 * mThickness)
        return;
    if (x * x + y * y <= headOffset * headOffset) {
        headOffset = 0;
    }
    Vector2 unitVector = (Vector2){x, y} / sqrt(x * x + y * y);

    Vector2 inverseVector = {unitVector.y, -unitVector.x};

    Vector2 headDestination = {scaledDestination.x - unitVector.x * headOffset,
                               scaledDestination.y - unitVector.y * headOffset};

    // Draw arrow head
    Vector2 arrowPoint = headDestination;
    Vector2 arrowSide1 = headDestination - unitVector * 2 * mThickness
                       + inverseVector * 1.5 * mThickness;
    Vector2 arrowSide2 = headDestination - unitVector * 2 * mThickness
                       - inverseVector * 1.5 * mThickness;

    DrawTriangle(arrowPoint + inverseVector * mSideOffset,
                 arrowSide1 + inverseVector * mSideOffset,
                 arrowSide2 + inverseVector * mSideOffset, mColor);

    // Draw arrow line
    DrawLineEx(source + inverseVector * mSideOffset,
               headDestination - unitVector * 2 * mThickness
                   + inverseVector * mSideOffset,
               mThickness, mColor);
}

void Arrow::drawLine(Vector2 source, Vector2 destination) {
    DrawLineEx(source, destination, mThickness, mColor);
}

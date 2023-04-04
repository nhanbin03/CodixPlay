#ifndef VISUALOBJECTS_ARROW_H
#define VISUALOBJECTS_ARROW_H

#include "VisualObject.h"

class Arrow {
public:
    const int DEFAULT_THICKNESS = 10;

public:
    Arrow();
    ~Arrow();

    void draw();

    void setSource(Vector2 position);
    void setDestination(Vector2 position);

    void setThickness(int thickness);

private:
    Vector2 mSource, mDestination;
    int mThickness;

    Color mColor;
};

#endif // VISUALOBJECTS_ARROW_H

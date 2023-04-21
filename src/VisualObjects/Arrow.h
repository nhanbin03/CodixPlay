#ifndef VISUALOBJECTS_ARROW_H
#define VISUALOBJECTS_ARROW_H

#include "VisualObject.h"

class Arrow : public VisualObject {
public:
    static constexpr int DEFAULT_THICKNESS = 5;

public:
    Arrow(bool isCircular = false);
    ~Arrow();

    void draw();
    void regularDraw();
    void circularDraw();

    void setSource(Vector2 position);
    Vector2 getSource() const;

    void setDestination(Vector2 position);
    Vector2 getDestination() const;

    void setThickness(int thickness);

    void setCircular(bool isCircular);
    bool isCircular() const;

private:
    Vector2 mSource, mDestination;
    int mThickness{DEFAULT_THICKNESS};

    Color mColor{VisualColor::getReferenceColor()};

    bool mIsCircular;

private:
    void drawArrow(Vector2 source, Vector2 destination, float scale,
                   int headOffset = 0);
    void drawLine(Vector2 source, Vector2 destination);
};

#endif // VISUALOBJECTS_ARROW_H

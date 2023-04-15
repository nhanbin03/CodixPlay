#ifndef VISUALOBJECTS_ARROW_H
#define VISUALOBJECTS_ARROW_H

#include "VisualObject.h"

class Arrow : public VisualObject {
public:
    static constexpr int DEFAULT_THICKNESS = 5;

public:
    Arrow();
    ~Arrow();

    void draw();

    void setSource(Vector2 position);
    Vector2 getSource() const;

    void setDestination(Vector2 position);
    Vector2 getDestination() const;

    void setThickness(int thickness);

private:
    Vector2 mSource, mDestination;
    int mThickness{DEFAULT_THICKNESS};

    Color mColor{VisualColor::getReferenceColor()};
};

#endif // VISUALOBJECTS_ARROW_H

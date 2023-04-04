#ifndef VISUALOBJECTS_CIRCLENODE_H
#define VISUALOBJECTS_CIRCLENODE_H

#include "VisualObject.h"

#include "raylib.h"

#include <string>

class CircleNode : public VisualObject {
public:
    CircleNode();
    ~CircleNode();

    void draw();

    void setValue(int value);
    int getValue() const;

    void setValueColor(Color color);

    void setColor(Color color);

private:
    float mRadius{ELEMENT_SIZE / 2};

    int mValue{0};
    Color mValueColor{WHITE};

    Color mColor{BLACK};
};

#endif // VISUALOBJECTS_CIRCLENODE_H

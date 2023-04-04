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
    float mRadius;

    int mValue;
    Color mValueColor;

    Color mColor;
    
};

#endif // VISUALOBJECTS_CIRCLENODE_H

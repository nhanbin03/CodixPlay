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
    Color getValueColor() const;

    void setColor(Color color);
    Color getColor() const;

    void setBorderColor(Color color);
    Color getBorderColor() const;

private:
    float mRadius{ELEMENT_SIZE / 2};

    int mValue{0};
    Color mValueColor{VisualColor::getPrimaryColor()};

    Color mColor{AppColor::BACKGROUND_2};

    Color mBorderColor{VisualColor::getPrimaryColor()};
};

#endif // VISUALOBJECTS_CIRCLENODE_H

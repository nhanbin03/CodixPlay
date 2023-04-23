#ifndef VISUALOBJECTS_SQUARENODE_H
#define VISUALOBJECTS_SQUARENODE_H

#include "VisualObject.h"

#include "raylib.h"

#include <string>

class SquareNode : public VisualObject {
public:
    SquareNode();
    ~SquareNode();

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
    float mSize{ELEMENT_SIZE};

    int mValue{0};
    Color mValueColor{VisualColor::getPrimaryColor()};

    Color mColor{AppColor::BACKGROUND_2};

    Color mBorderColor{VisualColor::getPrimaryColor()};
};

#endif // VISUALOBJECTS_SQUARENODE_H

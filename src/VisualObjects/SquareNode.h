#ifndef VISUALOBJECTS_SQUARENODE_H
#define VISUALOBJECTS_SQUARENODE_H

#include "VisualObject.h"

#include "raylib.h"

#include <functional>
#include <string>

class SquareNode : public VisualObject {
public:
    static constexpr float NO_VALUE_ALPHA = 0.25;

public:
    SquareNode();
    ~SquareNode();

    void draw();

    void setValue(int value);
    int getValue() const;

    void removeValue();
    bool hasValue() const;

    void setValueColor(Color color);
    Color getValueColor() const;

    void setColor(Color color);
    Color getColor() const;

    void setBorderColor(Color color);
    Color getBorderColor() const;

    void setTransparency(float alpha);
    float getTransparency() const;

private:
    float mSize{ELEMENT_SIZE};

    bool mHasValue{false};
    int mValue{0};
    Color mValueColor{VisualColor::getPrimaryColor()};

    Color mColor{AppColor::BACKGROUND_2};

    Color mBorderColor{VisualColor::getPrimaryColor()};

    // std::function<Color(Color)> mColorFilter;
    float mTransparency{0.25};
};

#endif // VISUALOBJECTS_SQUARENODE_H

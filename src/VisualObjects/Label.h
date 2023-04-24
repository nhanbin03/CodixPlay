#ifndef VISUALOBJECTS_LABEL_H
#define VISUALOBJECTS_LABEL_H

#include "VisualObject.h"

#include <string>

class Label : public VisualObject {
public:
    static constexpr int TEXT_SIZE = 20;

public:
    explicit Label(std::string text = "");
    ~Label();

    void draw();

    void setText(std::string text);

    void setColor(Color color);

    void setSize(int size);

private:
    std::string mText;

    Color mColor{VisualColor::getReferenceColor()};

    int mSize{TEXT_SIZE};
};

#endif // VISUALOBJECTS_LABEL_H

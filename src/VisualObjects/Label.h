#ifndef VISUALOBJECTS_LABEL_H
#define VISUALOBJECTS_LABEL_H

#include "VisualObject.h"

#include <string>

class Label : public VisualObject {
public:
    static constexpr int TEXT_SIZE = 24;

public:
    explicit Label(std::string text = "");
    ~Label();

    void draw();

    void setText(std::string text);

    void setColor(Color color);

private:
    std::string mText;

    Color mColor{BLACK};

    int mSize{TEXT_SIZE};
};

#endif // VISUALOBJECTS_LABEL_H

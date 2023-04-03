#ifndef GUIS_TEXTINPUTBOX_H
#define GUIS_TEXTINPUTBOX_H

#include "GUIComponent.h"
#include "Button.h"

#include "raylib.h"

#include <string>

class NumberInputBox : public GUIComponent {
public:
    const int MAX_LEN = 3;

public:
    NumberInputBox(Rectangle bounds);
    ~NumberInputBox();

    void update(float dt);
    void draw();

    std::string getInputText();

    void setBorderThickness(int thickness);

private:
    void checkInteraction();

    bool isValid(int key);

private:
    Rectangle mBounds;
    Color mColor, mBorderColor;
    int mBorderThickness;

    std::string mInputText;
    Color mTextColor;

    bool mIsFocused;
};

#endif // GUIS_TEXTINPUTBOX_H

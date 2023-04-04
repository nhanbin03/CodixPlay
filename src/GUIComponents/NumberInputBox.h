#ifndef GUICOMPONENTS_TEXTINPUTBOX_H
#define GUICOMPONENTS_TEXTINPUTBOX_H

#include <string>

#include "Button.h"
#include "GUIComponent.h"
#include "raylib.h"

class NumberInputBox : public GUIComponent {
public:
    const int MAX_TEXT_LENGTH = 2;

public:
    NumberInputBox();
    explicit NumberInputBox(Rectangle bounds);
    ~NumberInputBox();

    void update(float dt);
    void draw();

    void setPosition(Vector2 position) override;

    void setSize(Vector2 size) override;

    std::string getInputText();

    void setBorderThickness(int thickness);

private:
    void checkInteraction();

    bool isValid(int key);

private:
    Rectangle mBounds;
    Color mColor{WHITE};
    Color mBorderColor{BLACK};
    int mBorderThickness;

    std::string mInputText;
    Color mTextColor{BLACK};

    bool mIsFocused{false};
};

#endif // GUICOMPONENTS_TEXTINPUTBOX_H

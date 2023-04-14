#ifndef GUICOMPONENTS_TEXTINPUTBOX_H
#define GUICOMPONENTS_TEXTINPUTBOX_H

#include <string>

#include "Button.h"
#include "GUIComponent.h"
#include "raylib.h"

class NumberInputBox : public GUIComponent {
public:
    static constexpr int MAX_TEXT_LENGTH = 2;

public:
    explicit NumberInputBox(Rectangle bounds);
    ~NumberInputBox();

    void update(float dt);
    void draw();

    std::string getInputText();

private:
    void checkInteraction();

    bool isValid(int key);

private:
    std::string mInputText;
    Color mTextColor{BLACK};

    bool mIsFocused{false};
};

#endif // GUICOMPONENTS_TEXTINPUTBOX_H

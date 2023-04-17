#ifndef GUICOMPONENTS_INPUTBOX_H
#define GUICOMPONENTS_INPUTBOX_H

#include <string>

#include "Button.h"
#include "GUIComponent.h"
#include "raylib.h"

class InputBox : public GUIComponent {
public:
    explicit InputBox(Rectangle bounds = {0, 0, 0, 0});
    ~InputBox();

    void update(float dt);
    void draw();

    std::string getInputText();

private:
    void checkInteraction();

private:
    std::string mInputText;
    Color mTextColor{BLACK};

    bool mIsFocused{false};
};

#endif // GUICOMPONENTS_INPUTBOX_H

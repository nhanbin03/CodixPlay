#ifndef BUTTON_H
#define BUTTON_H

#include "GUIComponent.h"

#include "raylib.h"

#include <string>
#include <functional>

class Button: public GUIComponent {
public:
    typedef std::function<void()> Callback;

    enum class ButtonState {
        None,
        Focused,
        Active
    };
public:
    explicit Button(Rectangle bounds = {0, 0, 0, 0});
    ~Button();

    void update(float dt);
    void draw();

    void setPosition(Vector2 position) override;
    
    void setSize(Vector2 size) override;

    void setCallback(Callback callback);

    void setText(const std::string text);
    void setTextSize(int size);

private:
    void checkInteraction();

private:
    ButtonState mState;

    Rectangle mButton;
    Color mColor;

    Callback mCallback;


    std::string mText;
    Color mTextColor;
    int mTextSize;

};  

#endif // BUTTON_H
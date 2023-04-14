#ifndef GUICOMPONENTS_BUTTON_H
#define GUICOMPONENTS_BUTTON_H

#include "GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <string>

class Button : public GUIComponent {
public:
    static constexpr int SEGMENTS = 100;

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
    void setColor(Color color);

    void setCallback(Callback callback);

    void setText(const std::string text);
    void setTextSize(int size);
    void setTextColor(Color color);

    void setBorderThickness(int thickness);
    void setBorderColor(Color color);

private:
    void checkInteraction();

private:
    ButtonState mState{ButtonState::None};

    Rectangle mButton;
    Color mColor{GRAY};

    Callback mCallback;

    std::string mText;
    Color mTextColor{WHITE};
    int mTextSize{0};

    int mBorderThickness{0};
    Color mBorderColor{BLACK};
};

#endif // GUICOMPONENTS_BUTTON_H

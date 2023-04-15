#ifndef GUICOMPONENTS_BUTTON_H
#define GUICOMPONENTS_BUTTON_H

#include "GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <memory>
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

    void setSize(Vector2 size);

    void setCallback(Callback callback);

    void setText(const std::string text);
    void setTextSize(int size);
    void setTextColor(Color color);

    void setTexture(Texture2D texture);

private:
    void checkInteraction();

private:
    ButtonState mState{ButtonState::None};

    Callback mCallback;

    std::string mText;
    Color mTextColor{WHITE};
    int mTextSize{0};

    Texture2D mTexture;
};

#endif // GUICOMPONENTS_BUTTON_H

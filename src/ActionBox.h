#ifndef ACTIONBOX_H
#define ACTIONBOX_H

#include "GUIComponents/Button.h"
#include "GUIComponents/GUIComponent.h"
#include "GUIComponents/InputBox.h"

#include "raylib.h"

#include <functional>
#include <map>
#include <string>

class ActionBox : public GUIComponent {
public:
    static constexpr int INPUT_LABEL_SIZE = 19;

public:
    struct Input {
        std::string label;
        std::string name;
        std::function<bool(std::string)> validator;
        int width;
    };

    typedef std::map<std::string, std::string> InputData;

public:
    ActionBox(Rectangle bounds, std::string title, std::vector<Input> inputs,
              std::function<void()> onClick);

    void update(float dt);
    void draw();

    void activate();
    void deactivate();

    std::pair<bool, InputData> getInputs() const;

private:
    std::string mTitle;
    std::vector<Input> mInputs;
    std::function<void()> mOnSelect;

    bool mIsActivated{false};

    std::vector<InputBox> mInputBoxes;
    Button mSelectButton;

    Color mTextColor;

private:
    void activeUpdate(float dt);
    void inactiveUpdate(float dt);

    void activeDraw();
    void inactiveDraw();
};
#endif // ACTIONBOX_H

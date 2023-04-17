#ifndef ACTIONTAB_H
#define ACTIONTAB_H

#include "ActionBox.h"
#include "GUIComponents/GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <map>
#include <string>

class ActionTab : public GUIComponent {
public:
    ActionTab();

    void update(float dt);
    void draw();

    void addActionSelector(std::string title,
                           std::vector<ActionBox::Input> inputs,
                           std::function<void(ActionBox::InputData)> onSubmit);

private:
    bool hasSelection() const;
    void select(unsigned index);
    void resetSelection();

    void setSubmitCallback();

private:
    std::vector<ActionBox> mActions;
    int mSelectedAction{-1};

    Button mSubmitButton;
    std::vector<std::function<void(ActionBox::InputData)>> mOnSubmits;
};

#endif // ACTIONTAB_H

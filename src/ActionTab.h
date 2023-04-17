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

    void addActionSelector(
        std::string title, std::vector<ActionBox::Input> inputs,
        std::function<void(std::map<std::string, std::string>)> onSubmit);

private:
    bool hasSelection() const;
    void select(unsigned index);
    void resetSelection();

private:
    std::vector<ActionBox> mActions;
    int mSelectedAction{-1};
};

#endif // ACTIONTAB_H

#ifndef ACTIONCONTAINER_H
#define ACTIONCONTAINER_H

#include "ActionTab.h"
#include "GUIComponents/GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <map>
#include <string>

class ActionContainer : public GUIComponent {
public:
    enum class TabID {
        None,
        Initialize,
        Insert,
        Remove,
        Update,
        Search
    };

public:
    ActionContainer();

    void update(float dt);
    void draw();

    void addTab(TabID id);
    ActionTab& getTab(TabID id);

private:
    bool hasSelection() const;
    void select(TabID id);
    void resetSelection();

private:
    std::map<TabID, ActionTab> mTabs;
    std::vector<Button> mTabButtons;
    TabID mSelectedTab{TabID::None};

    Rectangle mTabIndicator;
};

#endif // ACTIONCONTAINER_H

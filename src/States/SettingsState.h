#ifndef STATES_SETTINGSSTATE_H
#define STATES_SETTINGSSTATE_H

#include "State.h"

class SettingsState : public State {
public:
    SettingsState(StateStack &stack, Context context);

    bool update(float dt);
    void draw();
};

#endif // STATES_SETTINGSSTATE_H

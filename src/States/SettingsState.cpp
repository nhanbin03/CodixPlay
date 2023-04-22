#include "SettingsState.h"

#include "raylib.h"

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Settings);
}

bool SettingsState::update(float dt) {
    mNavBar.update(dt);
    return true;
}

void SettingsState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mNavBar.draw();
}

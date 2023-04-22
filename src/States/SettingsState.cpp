#include "SettingsState.h"

#include "raylib.h"

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context) {
}

bool SettingsState::update(float dt) {
    return true;
}

void SettingsState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
}

#include "HomeState.h"

#include "raylib.h"

HomeState::HomeState(StateStack &stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Home);
}

bool HomeState::update(float dt) {
    mNavBar.update(dt);
    return true;
}

void HomeState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mNavBar.draw();
}

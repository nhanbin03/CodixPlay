#include "NavBar.h"

#include "Helper.h"

#include <cassert>

NavBar::NavBar() {
    mRect = {0, 0, 138, 950};
    mColor = AppColor::BACKGROUND_4;

    mLogoTexture = TextureHolder::getInstance().get(TextureID::Logo);
    scaleTexture(mLogoTexture, {94, 94});
}

void NavBar::update(float dt) {
    for (auto& p : mNavButtons) {
        p.second.update(dt);
    }
}

void NavBar::draw() {
    DrawRectangleRec(mRect, AppColor::BACKGROUND_4);
    DrawTexture(mLogoTexture, 22, 33, WHITE);
    for (auto& p : mNavButtons) {
        p.second.draw();
    }
}

void NavBar::addNav(NavID id, std::function<void()> navigate) {
    Button navButton;
    const int BUTTON_HEIGHT = 138;
    navButton.setPosition(
        (Vector2){0, 157 + BUTTON_HEIGHT * mNavButtons.size()});
    navButton.setSize({getSize().x, BUTTON_HEIGHT});
    navButton.setCornerRoundness(0);

    TextureID buttonTextureID;
    switch (id) {
        case NavID::Home:
            buttonTextureID = TextureID::NavHomeButton;
            break;
        case NavID::Settings:
            buttonTextureID = TextureID::NavSettingsButton;
            break;
    }
    navButton.setTexture(TextureHolder::getInstance().get(buttonTextureID));

    navButton.setColor(AppColor::BACKGROUND_4);
    navButton.setContentColor(AppColor::TEXT);
    navButton.setCallback(navigate);
    mNavButtons[id] = std::move(navButton);
}

void NavBar::setCurNav(NavID id) {
    auto found = mNavButtons.find(id);
    assert(found != mNavButtons.end());

    found->second.setContentColor(AppColor::TEXT_ACCENT);
}

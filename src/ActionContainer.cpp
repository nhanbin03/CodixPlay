#include "ActionContainer.h"

#include "ActionTab.h"

#include <cassert>
#include <iostream>

ActionContainer::ActionContainer() {
    mRect = {985, 0, 455, 617};
    mColor = AppColor::BACKGROUND_4;
}

void ActionContainer::update(float dt) {
    for (auto &btn : mTabButtons) {
        btn.update(dt);
    }
    for (auto &tab : mTabs) {
        tab.second->update(dt);
    }
}

void ActionContainer::draw() {
    DrawRectangleRec(mRect, mColor);
    for (auto &tab : mTabs) {
        tab.second->draw();
    }

    for (auto &btn : mTabButtons) {
        btn.draw();
    }

    DrawRectangleRounded(mTabIndicator, 0.5, ROUNDED_SEGMENTS,
                         AppColor::PRIMARY);

    DrawRectangleGradientV(mRect.x, 180, mRect.width, 7, GetColor(0x0000007F),
                           GetColor(0x00000000)); // Drop shadow effect
}

void ActionContainer::addTab(TabID id) {
    ActionTab::Ptr newTab = std::make_shared<ActionTab>();
    auto insertStatus = mTabs.emplace(id, newTab);
    assert(insertStatus.second == true);

    Button newButton;

    int startingX;
    if (mTabButtons.empty()) {
        startingX = mRect.x;
    } else {
        Rectangle lastButton = mTabButtons.back().getRect();
        startingX = lastButton.x + lastButton.width;
    }
    newButton.setRect((Rectangle){startingX, 89, 91, 91});
    newButton.setCornerRoundness(0);

    TextureID buttonTextureID;
    switch (id) {
        case TabID::Initialize:
            buttonTextureID = TextureID::InitializeTab;
            break;
        case TabID::Insert:
            buttonTextureID = TextureID::InsertTab;
            break;
        case TabID::Remove:
            buttonTextureID = TextureID::RemoveTab;
            break;
        case TabID::Update:
            buttonTextureID = TextureID::UpdateTab;
            break;
        case TabID::Search:
            buttonTextureID = TextureID::SearchTab;
            break;
    }
    newButton.setTexture(TextureHolder::getInstance().get(buttonTextureID));

    newButton.setColor(AppColor::BACKGROUND_4);
    newButton.setContentColor(AppColor::TEXT);

    newButton.setCallback([this, id, newButton]() {
        this->select(id);

        Rectangle rect = newButton.getRect();
        this->mTabIndicator = {rect.x + 29, rect.y + 85, 33, 4};
    });

    mTabButtons.push_back(newButton);

    if (mTabButtons.size() == 1) {
        newButton.triggerCallback();
    }
}

ActionTab::Ptr ActionContainer::getTab(TabID id) const {
    return mTabs.at(id);
}

bool ActionContainer::hasSelection() const {
    return mSelectedTab != TabID::None;
}

void ActionContainer::select(TabID id) {
    if (hasSelection()) {
        mTabs[mSelectedTab]->deactivate();
    }
    mSelectedTab = id;
    mTabs[mSelectedTab]->activate();
}

void ActionContainer::resetSelection() {
    mSelectedTab = TabID::None;
}

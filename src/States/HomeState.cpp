#include "HomeState.h"
#include "../Helper.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

HomeState::HomeState(StateStack &stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Home);

    addCategory(CategoryID::Array, "Array");

    addAlgoCard(CategoryID::Array, TextureID::StaticArrayCard,
                StateIDs::StaticArray);
    addAlgoCard(CategoryID::Array, TextureID::DynamicArrayCard,
                StateIDs::DynamicArray);

    addCategory(CategoryID::LinkedList, "Linked List");

    addAlgoCard(CategoryID::LinkedList, TextureID::SinglyLinkedListCard,
                StateIDs::SinglyLinkedList);
    addAlgoCard(CategoryID::LinkedList, TextureID::DoublyLinkedListCard,
                StateIDs::DoublyLinkedList);
    addAlgoCard(CategoryID::LinkedList, TextureID::CircularLinkedListCard,
                StateIDs::CircularLinkedList);
    addAlgoCard(CategoryID::LinkedList, TextureID::StackCard, StateIDs::Stack);
    addAlgoCard(CategoryID::LinkedList, TextureID::QueueCard, StateIDs::Queue);

    mHeroBanner = TextureHolder::getInstance().get(TextureID::HeroBanner);
    mBannerRect = {191, 51, 741, 194};
    scaleTexture(mHeroBanner, {mBannerRect.width, mBannerRect.height});
}

HomeState::~HomeState() {
}

bool HomeState::update(float dt) {
    mNavBar.update(dt);
    for (auto &category : mCategories) {
        category.second->update(dt);
    }
    mSettings.update(dt);
    return true;
}

void HomeState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mNavBar.draw();
    drawHeroBanner();
    for (auto &category : mCategories) {
        category.second->draw();
    }
    mSettings.draw();
}

void HomeState::drawHeroBanner() {
    DrawTexture(mHeroBanner, mBannerRect.x, mBannerRect.y, WHITE);
}

void HomeState::addCategory(CategoryID id, std::string title) {
    int positionY = 281 + (314 + 29) * mCategories.size();

    auto status = mCategories.emplace(
        id, std::make_unique<CategoryScroller>(positionY, title));

    assert(status.second == true);
}

CategoryScroller &HomeState::getCategory(CategoryID id) const {
    auto found = mCategories.find(id);
    assert(found != mCategories.end());
    return *found->second;
}

void HomeState::addAlgoCard(CategoryID categoryID, TextureID img,
                            StateIDs stateID) {
    auto &category = getCategory(categoryID);
    category.addCard(img, [this, stateID]() {
        this->requestStackPop();
        this->requestStackPush(stateID);
    });
}

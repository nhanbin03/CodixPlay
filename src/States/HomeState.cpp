#include "HomeState.h"

#include "raylib.h"

#include <cassert>
#include <iostream>

HomeState::HomeState(StateStack &stack, Context context)
: State(stack, context) {
    mNavBar.setCurNav(NavBar::NavID::Home);

    addCategory(CategoryID::Array, "Array");
    addAlgoCard(CategoryID::Array, "1");
    addAlgoCard(CategoryID::Array, "2");
    addAlgoCard(CategoryID::Array, "3");

    addCategory(CategoryID::LinkedList, "Linked List");
    addAlgoCard(CategoryID::LinkedList, "4");
    addAlgoCard(CategoryID::LinkedList, "5");
    addAlgoCard(CategoryID::LinkedList, "6");
}

HomeState::~HomeState() {
}

bool HomeState::update(float dt) {
    mNavBar.update(dt);
    for (auto &category : mCategories) {
        category.second->update(dt);
    }
    return true;
}

void HomeState::draw() {
    ClearBackground(AppColor::BACKGROUND_2);
    mNavBar.draw();
    for (auto &category : mCategories) {
        category.second->draw();
    }
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

void HomeState::addAlgoCard(CategoryID categoryID, std::string title) {
    auto &category = getCategory(categoryID);
    category.addCard(title, [this, title]() {
        std::cout << title << "\n";
    });
}

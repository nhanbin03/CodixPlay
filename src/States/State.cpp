#include "State.h"
#include "../StateStack.h"
#include "../Visualization.h"

State::State(StateStack &stack, Context context)
: mStack(&stack)
, mContext(context) {
    mNavBar.addNav(NavBar::NavID::Home, [this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::Home);
    });
    mNavBar.addNav(NavBar::NavID::Settings, [this]() {
        this->requestStackPop();
        this->requestStackPush(StateIDs::Settings);
    });
}

State::~State() {
}

void State::requestStackPush(StateIDs stateID) {
    mStack->pushState(stateID);
}

void State::requestStackPop() {
    mStack->popState();
}

void State::requestStackClear() {
    mStack->clearStates();
}

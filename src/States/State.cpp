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

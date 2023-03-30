#include "State.h"

State::State(StateStack &stack, Context context)
: mStack(&stack)
, mContext(context) {
}

State::~State() {
}
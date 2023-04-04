#ifndef STATE_H
#define STATE_H

#include "StateIdentifiers.h"

#include <memory>

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {};

public:
    State(StateStack &stack, Context context);
    virtual ~State();

    virtual bool update(float dt) = 0;
    virtual void draw() = 0;

protected:
    void requestStackPush(StateIDs stateID);
    void requestStackPop();
    void requestStackClear();

private:
    StateStack *mStack;
    Context mContext;
};

#endif // STATE_H

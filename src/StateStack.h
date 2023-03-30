#ifndef STATESTACK_H
#define STATESTACK_H

#include "State.h"
#include "StateIdentifiers.h"

#include <map>
#include <functional>

class StateStack {
public:
    explicit StateStack(State::Context context);

    template <typename StateType>
    void registerState(StateIDs stateID);

    void update(float dt);
    void draw();

    void pushState(StateIDs stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    enum class Action {
        Push,
        Pop,
        Clear
    };

    struct PendingChange {
        explicit PendingChange(Action action, StateIDs stateID = StateIDs::None);

        Action action;
        StateIDs stateID;
    };

private:
    void applyPendingChange();

    State::Ptr createState(StateIDs stateID);

private:
    std::vector<State::Ptr> mStack;
    std::vector<PendingChange> mPendingList;

    std::map<StateIDs, std::function<State::Ptr()>> mFactories;
    State::Context mContext;
};

#include "StateStack.inl"
#endif // STATESTACK_H

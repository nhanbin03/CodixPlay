#ifndef STATES_STATE_H
#define STATES_STATE_H

#include "../ResourceHolders/TextureHolder.h"
#include "../Visualization.h"
#include "StateIdentifiers.h"

#include <memory>

class StateStack;

class State {
public:
    typedef std::unique_ptr<State> Ptr;

    struct Context {
        Context(TextureHolder &textures);
        TextureHolder *textures;
    };

public:
    State(StateStack &stack, Context context);
    virtual ~State();

    virtual bool update(float dt) = 0;
    virtual void draw() = 0;

protected:
    Visualization mVisualization;

protected:
    void requestStackPush(StateIDs stateID);
    void requestStackPop();
    void requestStackClear();

private:
    StateStack *mStack;
    Context mContext;
};

#endif // STATES_STATE_H

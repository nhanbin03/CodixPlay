#ifndef STATES_HOMESTATE_H
#define STATES_HOMESTATE_H

#include "../CategoryScroller.h"

#include "State.h"

#include <map>

class HomeState : public State {
public:
    enum class CategoryID {
        Array,
        LinkedList
    };

public:
    HomeState(StateStack& stack, Context context);
    ~HomeState();

    bool update(float dt);
    void draw();

private:
    std::map<CategoryID, CategoryScroller::Ptr> mCategories;

private:
    void addCategory(CategoryID id, std::string title);
    void addAlgoCard(CategoryID categoryID, std::string title);

    CategoryScroller& getCategory(CategoryID id) const;
};

#endif // STATES_HOMESTATE_H

#ifndef CATEGORYSCROLLER_H
#define CATEGORYSCROLLER_H

#include "GUIComponents/Button.h"
#include "GUIComponents/GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <string>
#include <vector>

class CategoryScroller : public GUIComponent {
public:
    static constexpr float SLIDE_TIME = 1;

public:
    struct Card {
        Button clickBox;
        std::string title;
    };

public:
    CategoryScroller(int rectY);
    ~CategoryScroller();

    void update(float dt);
    void draw();

    void setTitle(std::string title);

    void addCard(std::string title, Button::Callback onClick);

private:
    std::string mTitle;

    std::vector<Card> mCardList;
    int mTracker{0};
    int mCardVirtualX, mAnimStartCardVirtualX, mAnimEndCardVirtualX;
    float mTimeCounter{0};

    Button mPrevButton, mNextButton;

private:
    void updateAnimCardVirtualX(float dt);

    float easeInOut(float from, float to, float time, float totalTime);
};

#endif // CATEGORYSCROLLER_H
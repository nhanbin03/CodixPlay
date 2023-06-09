#include "CategoryScroller.h"

#include "reasings.h"

#include <iostream>

CategoryScroller::CategoryScroller(int rectY, std::string title) {
    mRect = (Rectangle){138, rectY, 847, 314};
    mTitle = title;

    mPrevButton.setRect((Rectangle){160, rectY + 48, 24, 258});
    mPrevButton.setColor(AppColor::BACKGROUND_2);
    mPrevButton.setText("<");
    mPrevButton.setTextSize(40);
    mPrevButton.setContentColor(AppColor::BACKGROUND_4);
    mPrevButton.setInactivatedFilter([](Color) {
        return BLANK;
    });
    mPrevButton.setCallback([this]() {
        this->mTracker -= 2;
        this->mAnimStartCardVirtualX = this->mCardVirtualX;
        this->mAnimEndCardVirtualX += 2 * (352 + 25);
        this->mTimeCounter = this->SLIDE_TIME;
    });

    mNextButton.setRect((Rectangle){939, rectY + 48, 24, 258});
    mNextButton.setColor(AppColor::BACKGROUND_2);
    mNextButton.setText(">");
    mNextButton.setTextSize(40);
    mNextButton.setContentColor(AppColor::BACKGROUND_4);
    mNextButton.setInactivatedFilter([](Color) {
        return BLANK;
    });
    mNextButton.setCallback([this]() {
        this->mTracker += 2;
        this->mAnimStartCardVirtualX = this->mCardVirtualX;
        this->mAnimEndCardVirtualX -= 2 * (352 + 25);
        this->mTimeCounter = this->SLIDE_TIME;
    });

    mAnimStartCardVirtualX = mAnimEndCardVirtualX = mCardVirtualX = 197;
}

CategoryScroller::~CategoryScroller() {
}

void CategoryScroller::update(float dt) {
    if (this->mTracker == 0)
        this->mPrevButton.deactivate();
    else
        this->mPrevButton.activate();
    if (this->mTracker + 2 >= this->mCardList.size())
        this->mNextButton.deactivate();
    else
        this->mNextButton.activate();

    updateAnimCardVirtualX(dt);

    mPrevButton.update(dt);
    mNextButton.update(dt);
    int startingX = mCardVirtualX;
    for (auto& card : mCardList) {
        card.clickBox.setPosition((Vector2){startingX, mRect.y + 60});
        startingX += card.clickBox.getSize().x + 25;
    }
    if (mTracker < mCardList.size())
        mCardList[mTracker].clickBox.update(dt);
    if (mTracker + 1 < mCardList.size())
        mCardList[mTracker + 1].clickBox.update(dt);
}

void CategoryScroller::draw() {
    int titleSize = 50;
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, titleSize),
               mTitle.c_str(), {197, mRect.y}, titleSize, 0, AppColor::TEXT);

    mPrevButton.draw();
    mNextButton.draw();

    BeginScissorMode(184, mRect.y + 48, 755, 256);

    for (auto& card : mCardList) {
        card.clickBox.draw();
    }

    EndScissorMode();
}

void CategoryScroller::setTitle(std::string title) {
    mTitle = title;
}

void CategoryScroller::addCard(TextureID img, Button::Callback onClick) {
    Card newCard;
    newCard.clickBox.setSize({352, 234});
    newCard.clickBox.setTexture(TextureHolder::getInstance().get(img));
    newCard.clickBox.setCallback(onClick);

    mCardList.push_back(std::move(newCard));
}

void CategoryScroller::updateAnimCardVirtualX(float dt) {
    if (mTimeCounter > 0) {
        for (auto& card : mCardList) card.clickBox.deactivate();
        mTimeCounter -= dt;
        if (mTimeCounter <= 0) {
            mTimeCounter = 0;
            if (mTracker < mCardList.size())
                mCardList[mTracker].clickBox.activate();
            if (mTracker + 1 < mCardList.size())
                mCardList[mTracker + 1].clickBox.activate();
        }
        mCardVirtualX = easeInOut(mAnimStartCardVirtualX, mAnimEndCardVirtualX,
                                  SLIDE_TIME - mTimeCounter, SLIDE_TIME);
    }
}

float CategoryScroller::easeInOut(float from, float to, float time,
                                  float totalTime) {
    return EaseCubicInOut(time, from, to - from, totalTime);
}

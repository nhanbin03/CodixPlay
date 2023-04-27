#include "ControlBar.h"
#include "ResourceHolders/TextureHolder.h"

#include <cassert>
#include <iostream>

ControlBar::ControlBar(std::vector<VisualScene>& sceneTrack,
                       VisualScene& displayingScene)
: mSceneTrack(&sceneTrack)
, mDisplayingScene(&displayingScene) {
    assert(mSceneTrack->size() > 0);
    *mDisplayingScene = mSceneTrack->front();

    setColor(AppColor::BACKGROUND_3);
    setRect({138, 787, 847, 163});

    Button rewindBtn = Button({379, 870, 52, 52});
    formatButton(rewindBtn, TextureID::RewindSceneButton);
    rewindBtn.setCallback([this]() {
        this->setPause(true);
        this->rewindScene();
    });

    Button prevBtn = Button({457, 870, 52, 52});
    formatButton(prevBtn, TextureID::PrevSceneButton);
    prevBtn.setCallback([this]() {
        this->setPause(true);
        this->prevScene();
    });

    Button pauseBtn = Button({535, 870, 52, 52});
    formatButton(pauseBtn, TextureID::PauseSceneButton);
    pauseBtn.setCallback([this]() {
        this->togglePause();
    });

    Button nextBtn = Button({613, 870, 52, 52});
    formatButton(nextBtn, TextureID::NextSceneButton);
    nextBtn.setCallback([this]() {
        this->setPause(true);
        this->nextScene();
    });

    Button fowardBtn = Button({691, 870, 52, 52});
    formatButton(fowardBtn, TextureID::FowardSceneButton);
    fowardBtn.setCallback([this]() {
        this->setPause(true);
        this->fowardScene();
    });

    Button speedBtn = Button({875, 870, 52, 52});
    formatButton(speedBtn, TextureID::SpeedSceneButton);
    speedBtn.setCallback([this]() {
        this->mSpeedModifierHidden = !(this->mSpeedModifierHidden);
    });

    mBtnContainer.push_back(rewindBtn);
    mBtnContainer.push_back(prevBtn);
    mBtnContainer.push_back(pauseBtn);
    mBtnContainer.push_back(nextBtn);
    mBtnContainer.push_back(fowardBtn);
    mBtnContainer.push_back(speedBtn);

    mSpeedDownBtn.setRect({832, 796, 24, 24});
    mSpeedDownBtn.setText("-");
    mSpeedDownBtn.setTextSize(35);
    mSpeedDownBtn.setColor(BLANK);
    mSpeedDownBtn.setCallback([this]() {
        if (this->mSpeedTracker - 1 >= 0)
            this->mSpeedTracker--;
    });

    mSpeedUpBtn.setRect({947, 796, 24, 24});
    mSpeedUpBtn.setText("+");
    mSpeedUpBtn.setTextSize(35);
    mSpeedUpBtn.setColor(BLANK);
    mSpeedUpBtn.setCallback([this]() {
        if (this->mSpeedTracker + 1 < this->FACTORS_SIZE)
            this->mSpeedTracker++;
    });
}

ControlBar::~ControlBar() {
}

void ControlBar::update(float dt) {
    for (auto& btn : mBtnContainer) {
        btn.update(dt);
    }
    updateDisplayingScene(dt);
    if (mSpeedModifierHidden == false)
        updateSpeedModifier(dt);
}

void ControlBar::draw() {
    DrawRectangleRec(mRect, mColor);
    for (auto& btn : mBtnContainer) {
        btn.draw();
    }
    if (mSpeedModifierHidden == false)
        drawSpeedModifier();
}

void ControlBar::reset() {
    rewindScene();
    setPause(false);
}

int ControlBar::getTracker() const {
    return mTracker;
}

void ControlBar::rewindScene() {
    *mDisplayingScene = mSceneTrack->front();
    mTracker = 0;
}

void ControlBar::prevScene() {
    if (mTracker > 0) {
        mActionStatus = Action::Prev;
        *mDisplayingScene = (*mSceneTrack)[mTracker];
        mTracker--;
        mTimeCounter = 0;
    }
}

void ControlBar::togglePause() {
    setPause(!mIsPaused);
}

void ControlBar::nextScene() {
    if (mTracker + 1 < mSceneTrack->size()) {
        mActionStatus = Action::Next;
        *mDisplayingScene = (*mSceneTrack)[mTracker];
        mTracker++;
        mTimeCounter = 0;
    }
}

void ControlBar::fowardScene() {
    *mDisplayingScene = mSceneTrack->back();
    mTracker = mSceneTrack->size() - 1;
}

void ControlBar::setPause(bool pause) {
    mIsPaused = pause;
    if (mIsPaused == true)
        mBtnContainer[2].setTexture(
            TextureHolder::getInstance().get(TextureID::PlaySceneButton));
    else
        mBtnContainer[2].setTexture(
            TextureHolder::getInstance().get(TextureID::PauseSceneButton));
}

void ControlBar::updateDisplayingScene(float dt) {
    float speed = dt * FACTORS[mSpeedTracker];
    *mDisplayingScene = (*mSceneTrack)[mTracker];
    if (mActionStatus != Action::None || mIsPaused == false) {
        if (mTimeCounter < ANIMATION_TIME) {
            mTimeCounter += speed;
            if (mTimeCounter > ANIMATION_TIME)
                mTimeCounter = ANIMATION_TIME;
            int lastTracker;
            if (mActionStatus == Action::Prev) {
                lastTracker = mTracker + 1;
            } else {
                lastTracker = mTracker - 1;
            }
            if (lastTracker < mSceneTrack->size())
                *mDisplayingScene = VisualScene::transitionScene(
                    (*mSceneTrack)[lastTracker], (*mSceneTrack)[mTracker],
                    mTimeCounter, ANIMATION_TIME);
        } else {
            if (mIsPaused) {
                mActionStatus = Action::None;
            } else {
                nextScene();
            }
        }
    }
}

void ControlBar::updateSpeedModifier(float dt) {
    mSpeedDownBtn.update(dt);
    mSpeedUpBtn.update(dt);
}

void ControlBar::drawSpeedModifier() {
    DrawRectangleRounded({824, 729, 154, 132}, 0.5,
                         GUIComponent::ROUNDED_SEGMENTS,
                         ColorAlpha(AppColor::BACKGROUND_1, 0.6));

    std::string title = "Speed";
    int titleSize = 24;
    Font titleFont = FontHolder::getInstance().get(FontID::Inter, titleSize);
    Vector2 titleBounds = MeasureTextEx(titleFont, title.c_str(), titleSize, 0);
    DrawTextEx(titleFont, title.c_str(), {901 - titleBounds.x / 2, 738},
               titleSize, 0, AppColor::TEXT);

    std::string speed = FACTORS_STR[mSpeedTracker];
    int speedSize = 40;
    Font speedFont = FontHolder::getInstance().get(FontID::Inter, speedSize);
    Vector2 speedBounds = MeasureTextEx(speedFont, speed.c_str(), speedSize, 0);
    DrawTextEx(speedFont, speed.c_str(), {901 - speedBounds.x / 2, 788},
               speedSize, 0, AppColor::TEXT);

    mSpeedDownBtn.draw();
    mSpeedUpBtn.draw();
}

void ControlBar::formatButton(Button& btn, TextureID id) {
    btn.setColor(AppColor::BACKGROUND_3);
    btn.setContentColor(AppColor::TEXT);
    btn.setTexture(TextureHolder::getInstance().get(id));
}

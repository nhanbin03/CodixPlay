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

    mBtnContainer.push_back(rewindBtn);
    mBtnContainer.push_back(prevBtn);
    mBtnContainer.push_back(pauseBtn);
    mBtnContainer.push_back(nextBtn);
    mBtnContainer.push_back(fowardBtn);
}

ControlBar::~ControlBar() {
}

void ControlBar::update(float dt) {
    for (auto& btn : mBtnContainer) {
        btn.update(dt);
    }
    updateDisplayingScene(dt);
}

void ControlBar::draw() {
    DrawRectangleRec(mRect, mColor);
    for (auto& btn : mBtnContainer) {
        btn.draw();
    }
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
    std::cout << mTracker << " " << mSceneTrack->size() << "\n";
    if (mIsPaused == true)
        mBtnContainer[2].setTexture(
            TextureHolder::getInstance().get(TextureID::PlaySceneButton));
    else
        mBtnContainer[2].setTexture(
            TextureHolder::getInstance().get(TextureID::PauseSceneButton));
}

void ControlBar::updateDisplayingScene(float dt) {
    *mDisplayingScene = (*mSceneTrack)[mTracker];
    if (mActionStatus != Action::None || mIsPaused == false) {
        if (mTimeCounter < ANIMATION_TIME) {
            mTimeCounter += dt;
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

void ControlBar::formatButton(Button& btn, TextureID id) {
    btn.setColor(AppColor::BACKGROUND_3);
    btn.setContentColor(AppColor::TEXT);
    btn.setTexture(TextureHolder::getInstance().get(id));
}

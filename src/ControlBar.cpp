#include "ControlBar.h"

#include <cassert>
#include <iostream>

ControlBar::ControlBar(std::vector<VisualScene>& sceneTrack,
                       VisualScene& displayingScene)
: mSceneTrack(&sceneTrack)
, mDisplayingScene(&displayingScene) {
    assert(mSceneTrack->size() > 0);
    *mDisplayingScene = mSceneTrack->front();

    Button rewindBtn = Button({379, 870, 52, 52});
    rewindBtn.setCallback([this]() {
        this->mIsPaused = true;
        this->rewindScene();
    });
    Button prevBtn = Button({457, 870, 52, 52});
    prevBtn.setCallback([this]() {
        this->mIsPaused = true;
        this->prevScene();
    });
    Button pauseBtn = Button({535, 870, 52, 52});
    pauseBtn.setCallback([this]() {
        this->mIsPaused = true;
        this->togglePause();
    });
    Button nextBtn = Button({613, 870, 52, 52});
    nextBtn.setCallback([this]() {
        this->mIsPaused = true;
        this->nextScene();
    });
    Button fowardBtn = Button({691, 870, 52, 52});
    fowardBtn.setCallback([this]() {
        this->mIsPaused = true;
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
    mIsPaused = false;
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
    mIsPaused = !mIsPaused;
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

void ControlBar::updateDisplayingScene(float dt) {
    if (mActionStatus != Action::None || mIsPaused == false) {
        mTimeCounter += dt;
        if (mTimeCounter < ANIMATION_TIME) {
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
    } else {
        *mDisplayingScene = (*mSceneTrack)[mTracker];
    }
}

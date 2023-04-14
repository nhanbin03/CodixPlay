#include "ControlBar.h"

#include <cassert>
#include <iostream>

ControlBar::ControlBar(std::vector<VisualScene>& sceneTrack,
                       VisualScene& displayingScene)
: mSceneTrack(&sceneTrack)
, mDisplayingScene(&displayingScene) {
    assert(mSceneTrack->size() > 0);
    *mDisplayingScene = mSceneTrack->front();

    Button rewindBtn = Button({100, 700, 50, 50});
    rewindBtn.setCallback([this]() {
        this->rewindScene();
    });
    Button prevBtn = Button({200, 700, 50, 50});
    prevBtn.setCallback([this]() {
        this->prevScene();
    });
    Button pauseBtn = Button({300, 700, 50, 50});
    pauseBtn.setCallback([this]() {
        this->togglePause();
    });
    Button nextBtn = Button({400, 700, 50, 50});
    nextBtn.setCallback([this]() {
        this->nextScene();
    });
    Button fowardBtn = Button({500, 700, 50, 50});
    fowardBtn.setCallback([this]() {
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

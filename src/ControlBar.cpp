#include "ControlBar.h"

#include <cassert>

ControlBar::ControlBar(std::vector<VisualScene>& sceneTrack,
                       VisualScene& displayingScene)
: mSceneTrack(&sceneTrack)
, mDisplayingScene(&displayingScene)
, mTracker(0) {
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
    Button nextBtn = Button({300, 700, 50, 50});
    nextBtn.setCallback([this]() {
        this->nextScene();
    });
    Button fowardBtn = Button({400, 700, 50, 50});
    fowardBtn.setCallback([this]() {
        this->fowardScene();
    });

    mBtnContainer.push_back(rewindBtn);
    mBtnContainer.push_back(prevBtn);
    mBtnContainer.push_back(nextBtn);
    mBtnContainer.push_back(fowardBtn);
}

ControlBar::~ControlBar() {
}

void ControlBar::update(float dt) {
    *mDisplayingScene = (*mSceneTrack)[mTracker];
    for (auto& btn : mBtnContainer) {
        btn.update(dt);
    }
}

void ControlBar::draw() {
    for (auto& btn : mBtnContainer) {
        btn.draw();
    }
}

void ControlBar::reset() {
    rewindScene();
}

void ControlBar::rewindScene() {
    *mDisplayingScene = mSceneTrack->front();
    mTracker = 0;
}

void ControlBar::prevScene() {
    if (mTracker > 0) {
        *mDisplayingScene = (*mSceneTrack)[--mTracker];
    }
}

void ControlBar::nextScene() {
    if (mTracker + 1 < mSceneTrack->size()) {
        *mDisplayingScene = (*mSceneTrack)[++mTracker];
    }
}

void ControlBar::fowardScene() {
    *mDisplayingScene = mSceneTrack->back();
    mTracker = mSceneTrack->size() - 1;
}

#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include "GUIComponents/Button.h"
#include "VisualScene.h"

#include "raylib.h"

#include <vector>

class ControlBar {
public:
    static constexpr float ANIMATION_TIME = 0.5f;

public:
    ControlBar(std::vector<VisualScene> &sceneTrack,
               VisualScene &displayingScene);
    ~ControlBar();

    void update(float dt);
    void draw();

    void reset();

    void setPosition(Vector2 position);
    Vector2 getPosition() const;

    void setSize(Vector2 size);
    Vector2 getSize() const;

private:
    enum class Action {
        None,
        Prev,
        Next
    };

private:
    Vector2 mPosition, mSize;

    std::vector<VisualScene> *mSceneTrack;
    VisualScene *mDisplayingScene;

    int mTracker{0};

    std::vector<Button> mBtnContainer;

    Action mActionStatus{Action::None};
    float mTimeCounter;

private:
    void rewindScene();
    void prevScene();
    void nextScene();
    void fowardScene();
};

#endif // CONTROLBAR_H

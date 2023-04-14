#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include "GUIComponents/Button.h"
#include "VisualScene.h"

#include "raylib.h"

#include <vector>

class ControlBar : public GUIComponent {
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
    bool mIsPaused{false};

    std::vector<Button> mBtnContainer;

    Action mActionStatus{Action::None};
    float mTimeCounter;

private:
    void rewindScene();
    void prevScene();
    void togglePause();
    void nextScene();
    void fowardScene();

    void updateDisplayingScene(float dt);
};

#endif // CONTROLBAR_H

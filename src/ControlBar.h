#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include "GUIComponents/Button.h"
#include "VisualScene.h"

#include "raylib.h"

#include <vector>

class ControlBar {
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
    Vector2 mPosition, mSize;

    std::vector<VisualScene> *mSceneTrack;
    VisualScene *mDisplayingScene;

    int mTracker;

    std::vector<Button> mBtnContainer;

private:
    void rewindScene();
    void prevScene();
    void nextScene();
    void fowardScene();
};

#endif // CONTROLBAR_H

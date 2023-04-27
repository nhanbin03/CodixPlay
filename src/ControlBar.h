#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include "ColorPalettes/AppColorPalette.h"
#include "GUIComponents/Button.h"
#include "ResourceHolders/ResourceIdentifiers.h"
#include "VisualScene.h"

#include "raylib.h"

#include <vector>

class ControlBar : public GUIComponent {
public:
    static constexpr float ANIMATION_TIME = 0.7f;
    static constexpr int FACTORS_SIZE = 6;
    static constexpr float FACTORS[] = {0.25f, 0.5f, 1.0f, 2.0f, 3.0f, 4.0f};
    static constexpr char *FACTORS_STR[] = {"0.25", "0.5", "1.0",
                                            "2.0",  "3.0", "4.0"};
    static constexpr int PLAYER_BAR_LENGTH = 611;

public:
    ControlBar(std::vector<VisualScene> &sceneTrack,
               VisualScene &displayingScene);
    ~ControlBar();

    void update(float dt);
    void draw();

    void reset();

    int getTracker() const;

private:
    enum class Action {
        None,
        Prev,
        Next
    };

private:
    std::vector<VisualScene> *mSceneTrack;
    VisualScene *mDisplayingScene;

    int mTracker{0};
    bool mIsPaused{false};

    std::vector<Button> mBtnContainer;

    Action mActionStatus{Action::None};
    float mTimeCounter{0};

    int mCurrentBarLength;

    int mSpeedTracker{2};
    bool mSpeedModifierHidden{true};
    Button mSpeedUpBtn, mSpeedDownBtn;

private:
    void rewindScene();
    void prevScene();
    void togglePause();
    void nextScene();
    void fowardScene();

    void setPause(bool pause);

    void updateDisplayingScene(float dt);
    void updateSpeedModifier(float dt);

    void drawPlayBar();
    void drawSpeedModifier();

    void formatButton(Button &btn, TextureID id);

    int getBarLength(int tracker);
};
#endif // CONTROLBAR_H

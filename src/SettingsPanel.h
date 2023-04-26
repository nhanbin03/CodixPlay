#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include "ColorPalettes/VisualColorPalette.h"
#include "GUIComponents/Button.h"
#include "GUIComponents/GUIComponent.h"

#include "raylib.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

class SettingsPanel : public GUIComponent {
public:
    SettingsPanel();

    void update(float dt);
    void draw();

private:
    std::vector<Button::Ptr> mPrimary, mSecondary, mTertiary, mReference;
    Rectangle mPrimaryInd, mSecondaryInd, mTertiaryInd, mReferenceInd;

private:
    void populatePrimaryPalette(std::vector<Button::Ptr> &palette, int posY);
    void populateSecondaryPalette(std::vector<Button::Ptr> &palette, int posY);
    void populateTertiaryPalette(std::vector<Button::Ptr> &palette, int posY);
    void populateReferencePalette(std::vector<Button::Ptr> &palette, int posY);
};

#endif // SETTINGSPANEL_H

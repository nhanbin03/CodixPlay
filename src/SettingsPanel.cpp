#include "SettingsPanel.h"

// Yeah this file contains loads of boilerplate, can't help tho

SettingsPanel::SettingsPanel() {
    mRect = {985, 0, 455, 950};
    mColor = AppColor::BACKGROUND_4;

    mIcon = TextureHolder::getInstance().get(TextureID::SettingIcon);

    mToggleButton.setRect({985, 0, 455, 113});
    mToggleButton.setColor(mColor);
    mToggleButton.setCornerRoundness(0);
    mToggleButton.setCallback([this]() {
        this->mIsHidden = !(this->mIsHidden);
    });

    populatePrimaryPalette(mPrimary, 215);
    populateSecondaryPalette(mSecondary, 399);
    populateTertiaryPalette(mTertiary, 583);
    populateReferencePalette(mReference, 767);
}

void SettingsPanel::update(float dt) {
    mToggleButton.update(dt);
    if (mIsHidden)
        return;
    for (auto it : mPrimary) {
        it->update(dt);
        if (ColorToInt(VisualColor::getPrimaryColor())
            == ColorToInt(it->getColor()))
            mPrimaryInd = it->getRect();
    }
    for (auto it : mSecondary) {
        it->update(dt);
        if (ColorToInt(VisualColor::getSecondaryColor())
            == ColorToInt(it->getColor()))
            mSecondaryInd = it->getRect();
    }
    for (auto it : mTertiary) {
        it->update(dt);
        if (ColorToInt(VisualColor::getTertiaryColor())
            == ColorToInt(it->getColor()))
            mTertiaryInd = it->getRect();
    }
    for (auto it : mReference) {
        it->update(dt);
        if (ColorToInt(VisualColor::getReferenceColor())
            == ColorToInt(it->getColor()))
            mReferenceInd = it->getRect();
    }
}

void SettingsPanel::draw() {
    DrawRectangleRec(mRect, mColor);
    mToggleButton.draw();
    DrawTexture(mIcon, 1005, 20, AppColor::TEXT);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, 40),
               "Settings", {1100, 36}, 40, 0, AppColor::TEXT);
    DrawLine(985, 113, 1440, 113, AppColor::BACKGROUND_1);
    if (mIsHidden)
        return;

    // Draw text
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, 34),
               "Primary Color", {1023, 163}, 34, 0, AppColor::TEXT);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, 34),
               "Secondary Color", {1023, 347}, 34, 0, AppColor::TEXT);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, 34),
               "Tertiary Color", {1023, 531}, 34, 0, AppColor::TEXT);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter_Bold, 34),
               "Reference Color", {1023, 715}, 34, 0, AppColor::TEXT);

    // Draw color picker
    for (auto it : mPrimary) {
        it->draw();
    }
    for (auto it : mSecondary) {
        it->draw();
    }
    for (auto it : mTertiary) {
        it->draw();
    }
    for (auto it : mReference) {
        it->draw();
    }
    float cornerRoundess = 0.3;

    // Round overall corner
    DrawRectangleRoundedLines({1016, 215, 393, 88}, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7, mColor);
    DrawRectangleRoundedLines({1016, 399, 393, 88}, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7, mColor);
    DrawRectangleRoundedLines({1016, 583, 393, 88}, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7, mColor);
    DrawRectangleRoundedLines({1016, 767, 393, 88}, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7, mColor);

    // Draw indicator
    DrawRectangleRoundedLines(mPrimaryInd, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7,
                              AppColor::TEXT);
    DrawRectangleRoundedLines(mSecondaryInd, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7,
                              AppColor::TEXT);
    DrawRectangleRoundedLines(mTertiaryInd, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7,
                              AppColor::TEXT);
    DrawRectangleRoundedLines(mReferenceInd, cornerRoundess,
                              GUIComponent::ROUNDED_SEGMENTS, 7,
                              AppColor::TEXT);
}

void SettingsPanel::populatePrimaryPalette(std::vector<Button::Ptr>& palette,
                                           int posY) {
    for (int i = 0; i < VisualColor::OPTIONS_SIZE; i++) {
        Button::Ptr colorPicker = std::make_shared<Button>();
        colorPicker->setSize({98, 88});
        colorPicker->setPosition((Vector2){1016 + 98 * i, posY});
        colorPicker->setColor(VisualColor::OPTIONS[i]);
        colorPicker->setCornerRoundness(0);
        colorPicker->setCallback([this, i]() {
            VisualColor::setPrimaryColor(VisualColor::ColorID(i));
        });
        mPrimary.push_back(colorPicker);
    }
}

void SettingsPanel::populateSecondaryPalette(std::vector<Button::Ptr>& palette,
                                             int posY) {
    for (int i = 0; i < VisualColor::OPTIONS_SIZE; i++) {
        Button::Ptr colorPicker = std::make_shared<Button>();
        colorPicker->setSize({98, 88});
        colorPicker->setPosition((Vector2){1016 + 98 * i, posY});
        colorPicker->setColor(VisualColor::OPTIONS[i]);
        colorPicker->setCornerRoundness(0);
        colorPicker->setCallback([this, i]() {
            VisualColor::setSecondaryColor(VisualColor::ColorID(i));
        });
        mSecondary.push_back(colorPicker);
    }
}

void SettingsPanel::populateTertiaryPalette(std::vector<Button::Ptr>& palette,
                                            int posY) {
    for (int i = 0; i < VisualColor::OPTIONS_SIZE; i++) {
        Button::Ptr colorPicker = std::make_shared<Button>();
        colorPicker->setSize({98, 88});
        colorPicker->setPosition((Vector2){1016 + 98 * i, posY});
        colorPicker->setColor(VisualColor::OPTIONS[i]);
        colorPicker->setCornerRoundness(0);
        colorPicker->setCallback([this, i]() {
            VisualColor::setTertiaryColor(VisualColor::ColorID(i));
        });
        mTertiary.push_back(colorPicker);
    }
}

void SettingsPanel::populateReferencePalette(std::vector<Button::Ptr>& palette,
                                             int posY) {
    for (int i = 0; i < VisualColor::OPTIONS_SIZE; i++) {
        Button::Ptr colorPicker = std::make_shared<Button>();
        colorPicker->setSize({98, 88});
        colorPicker->setPosition((Vector2){1016 + 98 * i, posY});
        colorPicker->setColor(VisualColor::OPTIONS[i]);
        colorPicker->setCornerRoundness(0);
        colorPicker->setCallback([this, i]() {
            VisualColor::setReferenceColor(VisualColor::ColorID(i));
        });
        mReference.push_back(colorPicker);
    }
}

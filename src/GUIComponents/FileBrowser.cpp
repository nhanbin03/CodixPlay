#include "FileBrowser.h"

#include <iostream>

FileBrowser::FileBrowser(Rectangle bounds) {
    mRect = bounds;
    mColor = WHITE;
    mBorderColor = BLACK;
    mBorderThickness = 1;

    mBrowseButton.setRect({mRect.x, mRect.y, mRect.width / 3, mRect.height});
    mBrowseButton.setText("Open");
    mBrowseButton.setCallback([this]() {
        const char* inputPath =
            tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
        if (inputPath != NULL) {
            this->mInputPath = inputPath;
        }
    });
}

FileBrowser::~FileBrowser() {
}

void FileBrowser::reset() {
    mInputPath = "";
}

void FileBrowser::update(float dt) {
    mBrowseButton.setRect({mRect.x, mRect.y, mRect.width / 3, mRect.height});
    mBrowseButton.update(dt);
}

void FileBrowser::draw() {
    DrawRectangleRounded(mRect, mCornerRoundness, ROUNDED_SEGMENTS, mColor);
    if (mBorderThickness != 0)
        DrawRectangleRoundedLines(mRect, mCornerRoundness, ROUNDED_SEGMENTS,
                                  mBorderThickness, mBorderColor);

    int textSize = mRect.height * 2 / 3;
    std::string displayText =
        mInputPath.substr(mInputPath.find_last_of("/\\") + 1);
    Vector2 textBounds =
        MeasureTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
                      mInputPath.c_str(), textSize, 0);
    Rectangle textDrawRect = {mRect.x + mRect.width / 3, mRect.y,
                              mRect.width - mRect.width / 3, mRect.height};
    BeginScissorMode(textDrawRect.x, textDrawRect.y, textDrawRect.width,
                     textDrawRect.height);
    DrawTextEx(FontHolder::getInstance().get(FontID::Inter, textSize),
               displayText.c_str(),
               {textDrawRect.x + textSize / 3,
                textDrawRect.y + textDrawRect.height / 2 - textBounds.y / 2},
               textSize, 0, mTextColor);
    EndScissorMode();
    mBrowseButton.draw();
}

void FileBrowser::setBorderThickness(int thickness) {
    mBorderThickness = thickness;
}

void FileBrowser::setCornerRoundness(float cornerRoundness) {
    mCornerRoundness = cornerRoundness;
    mBrowseButton.setCornerRoundness(cornerRoundness);
}

void FileBrowser::setButtonColor(Color color) {
    mBrowseButton.setColor(color);
}

void FileBrowser::setButtonContentColor(Color color) {
    mBrowseButton.setContentColor(color);
}

void FileBrowser::setButtonBorderColor(Color color) {
    mBrowseButton.setBorderColor(color);
}

std::string FileBrowser::getInputPath() const {
    return mInputPath;
}

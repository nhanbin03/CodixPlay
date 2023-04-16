#include "CodeHighlighter.h"

#include <cassert>
#include <iostream>

CodeHighlighter::CodeHighlighter() {
    mRect = {985, 617, 455, 333};
    mColor = AppColor::BACKGROUND_1;

    mIndexTrack.push_back({});
}

void CodeHighlighter::draw() {
    DrawRectangleRec(mRect, mColor);

    for (auto idx : mIndexTrack[mTracker]) {
        mCode[idx].second = true;
    }
    int lineHeight = mRect.height / MAX_LINES;
    int textSize = lineHeight * 2 / 3;
    int leftAlign = 32;
    for (int i = 0; i < mCode.size(); i++) {
        Color backgroundColor, codeColor;
        if (mCode[i].second) {
            backgroundColor = AppColor::CODE_ACCENT_BACKGROUND;
            codeColor = AppColor::CODE_ACCENT;
        } else {
            backgroundColor = mColor;
            codeColor = AppColor::CODE;
        }
        DrawRectangleRec((Rectangle){mRect.x, mRect.y + i * lineHeight,
                                     mRect.width, lineHeight},
                         backgroundColor);
        DrawTextEx(FontHolder::getInstance().get(FontID::Consolas, textSize),
                   mCode[i].first.c_str(),
                   {mRect.x + leftAlign,
                    mRect.y + i * lineHeight + lineHeight / 2 - textSize / 2},
                   textSize, 0, codeColor);
        mCode[i].second = false;
    }
}

void CodeHighlighter::reset() {
    mCode.clear();
    mIndexTrack.clear();
    mIndexTrack.push_back({});
    mTracker = 0;
}

void CodeHighlighter::addCode(std::string code) {
    mCode.push_back(std::make_pair(code, false));
}

void CodeHighlighter::highlightCode(std::vector<int> lines) {
    mIndexTrack.push_back(lines);
}

void CodeHighlighter::setTracker(int tracker) {
    mTracker = tracker;
    assert(mTracker >= 0 && mTracker < mIndexTrack.size());
}

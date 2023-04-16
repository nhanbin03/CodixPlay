#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include "GUIComponents/GUIComponent.h"

#include "raylib.h"

#include <string>
#include <vector>

class CodeHighlighter : public GUIComponent {
public:
    static constexpr int MAX_LINES = 9;

public:
    CodeHighlighter();

    void draw();

    void reset();
    void addCode(std::string code);

    void highlightCode(std::vector<int> lines);
    void setTracker(int tracker);

private:
    std::vector<std::pair<std::string, bool>>
        mCode; // pair of (code, isHighlighted)
    std::vector<std::vector<int>>
        mIndexTrack; // 2D array for highlighting multiple lines

    int mTracker{0};
};

#endif // CODEHIGHLIGHTER_H

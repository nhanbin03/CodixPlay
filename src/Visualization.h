#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "CodeHighlighter.h"
#include "ControlBar.h"
#include "VisualObjects/VisualObject.h"
#include "VisualScene.h"

#include "raylib.h"

#include <string>
#include <vector>

class Visualization : public GUIComponent {
public:
    Visualization();
    ~Visualization();

    void update(float dt);
    void draw();

    void reset(VisualScene initScene = VisualScene());

    void createNewScene();
    VisualScene getLastScene() const;

    int createBlock();
    void moveBlock(int blockID, Vector2 position);
    void moveBlockDelta(int blockID, Vector2 position);
    void colorBlock(int blockID, Color color);
    void highlightBlock(int blockID);
    void unhighlightBlock(int blockID);
    void setValueBlock(int blockID, int value);
    void removeValueBlock(int blockID);
    void removeBlock(int blockID);
    Vector2 getBlockPosition(int blockID) const;

    int createNode(int value);
    void moveNode(int nodeID, Vector2 position);
    void moveNodeDelta(int nodeID, Vector2 position);
    void colorNode(int nodeID, Color color); // Color and highlight node
    void highlightNode(int nodeID);
    void unhighlightNode(int nodeID);
    void updateNode(int nodeID, int value);
    void removeNode(int nodeID);
    Vector2 getNodePosition(int nodeID) const;

    int createArrow(Vector2 source, Vector2 destination);
    int createCircularArrow(Vector2 source, Vector2 destination);
    int createOffsetArrow(Vector2 source, Vector2 destination);
    void moveArrowSource(int arrowID, Vector2 source);
    void moveArrowDestination(int arrowID, Vector2 destination);
    void moveArrowDelta(int arrowID, Vector2 source, Vector2 destination);
    void removeArrow(int arrowID);

    int createLabel(const std::string text, Vector2 position = {0, 0});
    int createNodeLabel(const std::string text, int idAttached);
    void setSizeLabel(int labelID, int size);
    void moveLabel(int labelID, Vector2 position);
    void attachNodeLabel(int labelID, int idAttached);
    void updateLabel(int labelID, const std::string text);
    void removeLabel(int labelID);

    void addCode(std::string code);
    void highlightCode(std::vector<int> lines);

private:
    std::vector<VisualScene> mSceneTrack;
    VisualScene mDisplayingScene;

    ControlBar mControlBar;

    CodeHighlighter mCodeHighlighter;
};

#endif // VISUALIZATION_H

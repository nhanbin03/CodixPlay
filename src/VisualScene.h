#ifndef VISUALSCENE_H
#define VISUALSCENE_H

#include "GUIComponents/GUIComponent.h"
#include "VisualObjects/Arrow.h"
#include "VisualObjects/CircleNode.h"
#include "VisualObjects/Label.h"
#include "VisualObjects/SquareNode.h"
#include "VisualObjects/VisualObject.h"

#include "raylib.h"
#include "reasings.h"

#include <map>
#include <set>
#include <string>

class VisualScene : public GUIComponent {
public:
    VisualScene();
    ~VisualScene();

    static VisualScene transitionScene(const VisualScene& fromScene,
                                       const VisualScene& toScene, float time,
                                       float totalTime);
    static float easeInOut(float from, float to, float time, float totalTime);

    void draw();

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
    void colorNode(int nodeID, Color color);
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

    int createLabel(const std::string text, Vector2 position);
    int createNodeLabel(const std::string text, int idAttached);
    void setSizeLabel(int labelID, int size);
    void moveLabel(int labelID, Vector2 position);
    void attachNodeLabel(int labelID, int idAttached);
    void updateLabel(int labelID, const std::string text);
    void removeLabel(int labelID);

private:
    SquareNode& getBlock(int blockID);
    const SquareNode& getBlock(int blockID) const;

    CircleNode& getNode(int nodeID);
    const CircleNode& getNode(int nodeID) const;

    Arrow& getArrow(int arrowID);
    const Arrow& getArrow(int arrowID) const;

    Label& getLabel(int labelID);
    const Label& getLabel(int labelID) const;

    static Color easeInOutColor(Color fromColor, Color toColor, float time,
                                float totalTime);

    static void transitionBlock(const VisualScene& fromScene,
                                const VisualScene& toScene, float time,
                                float totalTime, VisualScene& visualScene);

    static void transitionNode(const VisualScene& fromScene,
                               const VisualScene& toScene, float time,
                               float totalTime, VisualScene& visualScene);
    static void transitionArrow(const VisualScene& fromScene,
                                const VisualScene& toScene, float time,
                                float totalTime, VisualScene& visualScene);
    static void transitionLabel(const VisualScene& fromScene,
                                const VisualScene& toScene, float time,
                                float totalTime, VisualScene& visualScene);

private:
    std::map<int, SquareNode> mBlockMap;
    std::map<int, CircleNode> mNodeMap;
    std::map<int, Arrow> mArrowMap;
    std::map<int, Label> mLabelMap;
};

#endif // VISUALSCENE_H

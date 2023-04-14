#ifndef VISUALSCENE_H
#define VISUALSCENE_H

#include "VisualObjects/Arrow.h"
#include "VisualObjects/CircleNode.h"
#include "VisualObjects/Label.h"
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

    void draw();

    void createArray(int size);
    void colorArrayElement(int index, Color color);
    void updateArrayElement(int index, int value);
    void removeArray();

    int createNode(int value);
    void moveNode(int nodeID, Vector2 position);
    void moveNodeDelta(int nodeID, Vector2 position);
    void colorNode(int nodeID, Color color);
    void colorValueNode(int nodeID, Color color);
    void updateNode(int nodeID, int value);
    void removeNode(int nodeID);
    Vector2 getNodePosition(int nodeID);

    int createArrow(Vector2 source, Vector2 destination);
    int createCircularArrow(Vector2 source, Vector2 destination);
    void moveArrowSource(int arrowID, Vector2 source);
    void moveArrowDestination(int arrowID, Vector2 destination);
    void moveArrowDelta(int arrowID, Vector2 source, Vector2 destination);
    void removeArrow(int arrowID);

    int createLabel(const std::string text, Vector2 position);
    int createNodeLabel(const std::string text, int idAttached);
    void moveLabel(int labelID, Vector2 position);
    void attachNodeLabel(int labelID, int idAttached);
    void updateLabel(int labelID, const std::string text);
    void removeLabel(int labelID);

private:
    CircleNode& getNode(int nodeID);
    Arrow& getArrow(int arrowID);
    Label& getLabel(int labelID);

    static float easeInOut(float from, float to, float time, float totalTime);

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
    std::map<int, CircleNode> mNodeMap;
    std::map<int, Arrow> mArrowMap;
    std::map<int, Label> mLabelMap;
};

#endif // VISUALSCENE_H

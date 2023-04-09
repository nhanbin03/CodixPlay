#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "ControlBar.h"
#include "VisualObjects/VisualObject.h"
#include "VisualScene.h"

#include "raylib.h"

#include <string>
#include <vector>

class Visualization {
public:
    Visualization(VisualScene initScene = VisualScene());
    ~Visualization();

    void update(float dt);
    void draw();

    void createNewScene();
    VisualScene getLastScene() const;

    void createArray(int size);
    void colorArrayElement(int index, Color color);
    void updateArrayElement(int index, int value);
    void removeArray();

    int createNode(int value);
    void moveNode(int nodeID, Vector2 position);
    void colorNode(int nodeID, Color color);
    void colorValueNode(int nodeID, Color color);
    void updateNode(int nodeID, int value);
    void removeNode(int nodeID);

    int createArrow(Vector2 source, Vector2 destination);
    int createCircularArrow(Vector2 source, Vector2 destination);
    void removeArrow(int arrowID);

    int createLabel(const std::string text, Vector2 position);
    void moveLabel(int labelID, Vector2 position);
    void updateLabel(int labelID, const std::string text);
    void removeLabel(int labelID);

private:
    std::vector<VisualScene> mSceneTrack;
    VisualScene mDisplayingScene;

    ControlBar mControlBar;
};

#endif // VISUALIZATION_H

#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "States/State.h"
#include "VisualObject.h"

#include "raylib.h"

#include <string>

class Visualization {
public:
    Visualization(State::Context context);
    ~Visualization();

    bool update(float dt);
    void draw();

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
};

#endif // VISUALIZATION_H

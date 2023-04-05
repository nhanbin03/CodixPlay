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
    void updateNode(int nodeID, int value);
    void removeNode(int nodeID);

    int createArrow(int sourceID, int destinationID);
    int createCircularArrow(int sourceID, int destinationID);
    void removeArrow(int arrowID);

    int createLabel(const std::string text, int nearbyObjectID);
    void moveLabel(int label, Vector2 position);
    void updateLabel(int label, const std::string text);
    void removeLabel(int label);
};

#endif // VISUALIZATION_H

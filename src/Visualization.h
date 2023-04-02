#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "State.h"
#include "VisualObject.h"

#include "raylib.h"


class Visualization {
public:
    Visualization(State::Context context);
    ~Visualization();

    bool update(float dt);
    void draw();

    void createArray(int size);
    void highlightArrayElement(int index, Color color);
    void updateArrayElement(int index, int value);
    void removeArray();

    VisualObject::Ptr createNode(int value);
    void moveNode(VisualObject::Ptr node, Vector2 position);
    void highlightNode(VisualObject::Ptr node, Color color);
    void updateNode(VisualObject::Ptr node, int value);
    void removeNode(VisualObject::Ptr node);

    VisualObject::Ptr createArrow(VisualObject::Ptr from, VisualObject::Ptr to);
    VisualObject::Ptr createCircularArrow(VisualObject::Ptr from, VisualObject::Ptr to);

    VisualObject::Ptr createLabel(const char* text, VisualObject::Ptr nearbyObject);
    void moveLabel(VisualObject::Ptr label);
    void updateLabel(VisualObject::Ptr label, const char* text);
    void removeLabel(VisualObject::Ptr label);
};

#endif // VISUALIZATION_H

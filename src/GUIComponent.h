#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "raylib.h"

class GUIComponent {
public:
    GUIComponent();
    virtual ~GUIComponent();

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    Vector2 getPosition() const;
    void setPosition(Vector2 position);

    Vector2 getSize() const;
    void setSize(Vector2 size);

private:
    Vector2 mPosition;
    Vector2 mSize;
};

#endif // GUICOMPONENT_H

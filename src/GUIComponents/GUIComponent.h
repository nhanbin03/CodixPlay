#ifndef GUICOMPONENTS_GUICOMPONENT_H
#define GUICOMPONENTS_GUICOMPONENT_H

#include "raylib.h"

class GUIComponent {
public:
    GUIComponent();
    virtual ~GUIComponent();

    virtual void update(float dt);
    virtual void draw() = 0;

    virtual Rectangle getRect() const;
    virtual void setRect(Rectangle rect);

    virtual Vector2 getPosition() const;
    virtual void setPosition(Vector2 position);

    virtual Vector2 getSize() const;
    virtual void setSize(Vector2 size);

private:
    Rectangle mRect;
};

#endif // GUICOMPONENTS_GUICOMPONENT_H

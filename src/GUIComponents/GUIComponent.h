#ifndef GUICOMPONENTS_GUICOMPONENT_H
#define GUICOMPONENTS_GUICOMPONENT_H

#include "../ColorPalettes/AppColorPalette.h"
#include "../ResourceHolders/FontHolder.h"

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

    void setColor(Color color);
    void setBorderThickness(int thickness);
    void setBorderColor(Color color);

protected:
    Rectangle mRect;
    Color mColor{BLANK};
    Color mBorderColor{BLANK};
    int mBorderThickness{0};
};

#endif // GUICOMPONENTS_GUICOMPONENT_H

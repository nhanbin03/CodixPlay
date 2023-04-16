#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "../ColorPalettes/AppColorPalette.h"
#include "../ColorPalettes/VisualColorPalette.h"
#include "../ResourceHolders/FontHolder.h"

#include "raylib.h"

#include <memory>

class VisualObject {
public:
    typedef std::unique_ptr<VisualObject> Ptr;

    static constexpr int ELEMENT_SIZE = 50;
    static constexpr int BORDER_THICKNESS = 5;

public:
    VisualObject();
    virtual ~VisualObject();

    virtual void draw() = 0;

    virtual void setPosition(Vector2 position);
    Vector2 getPosition() const;

    virtual void setScale(float scale);
    float getScale() const;

    void setZIndex(int zIndex);
    int getZIndex() const;

    int getObjectID() const;

private:
    Vector2 mPosition;
    float mScale{1};

    int mZIndex{0};

    static int objectIDTracker;
};

#endif // VISUALOBJECT_H

#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <memory>

#include "raylib.h"

class VisualObject {
public:
    typedef std::shared_ptr<VisualObject> Ptr;

    const int ELEMENT_SIZE = 70;

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

private:
    Vector2 mPosition;
    float mScale{1};

    int mZIndex{0};
};

#endif // VISUALOBJECT_H

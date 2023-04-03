#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <memory>

#include "raylib.h"
class VisualObject {
public:
    typedef std::shared_ptr<VisualObject> Ptr;

    VisualObject();
    virtual ~VisualObject();

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    void setPosition(Vector2 position);
    Vector2 getPosition();

    void setScale(float scale);
    float getScale();

private:
    Vector2 mPosition;
    float mScale;
};

#endif // VISUALOBJECT_H

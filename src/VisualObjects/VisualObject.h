#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <memory>

#include "raylib.h"
class VisualObject {
public:
    typedef std::shared_ptr<VisualObject> Ptr;

    const int ELEMENT_SIZE = 70;
    const int ARROW_LENGTH = 140;

public:
    VisualObject();
    virtual ~VisualObject();

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    void setPosition(Vector2 position);
    Vector2 getPosition() const;

    void setScale(float scale);
    float getScale() const;

private:
    Vector2 mPosition;
    float mScale;
};

#endif // VISUALOBJECT_H

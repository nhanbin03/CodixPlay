#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

class GUIComponent {
public:
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};

#endif // GUICOMPONENT_H

#include "VisualScene.h"

#include <cassert>
#include <memory>

VisualScene::VisualScene() {
}

VisualScene::~VisualScene() {
}

// Priority: label -> nodes/arrays -> arrow
void VisualScene::draw() {
    for (auto obj : mArrowMap) {
        obj.second.draw();
    }
    for (auto obj : mNodeMap) {
        obj.second.draw();
    }
    for (auto obj : mLabelMap) {
        obj.second.draw();
    }
}

int VisualScene::createNode(int value) {
    CircleNode newObject;
    int objectID = newObject.getObjectID();

    newObject.setValue(value);

    auto insertStatus = mNodeMap.emplace(objectID, newObject);

    assert(insertStatus.second == true);

    return objectID;
}

void VisualScene::moveNode(int nodeID, Vector2 position) {
    getNode(nodeID).setPosition(position);
}

void VisualScene::colorNode(int nodeID, Color color) {
    getNode(nodeID).setColor(color);
}

void VisualScene::colorValueNode(int nodeID, Color color) {
    getNode(nodeID).setValueColor(color);
}

void VisualScene::updateNode(int nodeID, int value) {
    getNode(nodeID).setValue(value);
}

void VisualScene::removeNode(int nodeID) {
    mNodeMap.erase(nodeID);
}

CircleNode& VisualScene::getNode(int nodeID) {
    auto found = mNodeMap.find(nodeID);
    assert(found != mNodeMap.end());

    return found->second;
}

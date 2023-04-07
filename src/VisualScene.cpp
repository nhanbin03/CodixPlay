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
    newObject.setValue(value);

    int objectID = newObject.getObjectID();
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

int VisualScene::createArrow(Vector2 source, Vector2 destination) {
    Arrow newObject;
    newObject.setSource(source);
    newObject.setDestination(destination);

    int objectID = newObject.getObjectID();
    auto insertStatus = mArrowMap.emplace(objectID, newObject);

    assert(insertStatus.second == true);

    return objectID;
}

void VisualScene::removeArrow(int arrowID) {
    mArrowMap.erase(arrowID);
}

int VisualScene::createLabel(const std::string text, Vector2 position) {
    Label newObject(text);
    newObject.setPosition(position);

    int objectID = newObject.getObjectID();
    auto insertStatus = mLabelMap.emplace(objectID, newObject);

    assert(insertStatus.second == true);

    return objectID;
}

void VisualScene::moveLabel(int labelID, Vector2 position) {
    getLabel(labelID).setPosition(position);
}

void VisualScene::updateLabel(int labelID, const std::string text) {
    getLabel(labelID).setText(text);
}

void VisualScene::removeLabel(int labelID) {
    mLabelMap.erase(labelID);
}

CircleNode& VisualScene::getNode(int nodeID) {
    auto found = mNodeMap.find(nodeID);
    assert(found != mNodeMap.end());

    return found->second;
}

Arrow& VisualScene::getArrow(int arrowID) {
    auto found = mArrowMap.find(arrowID);
    assert(found != mArrowMap.end());

    return found->second;
}

Label& VisualScene::getLabel(int labelID) {
    auto found = mLabelMap.find(labelID);
    assert(found != mLabelMap.end());

    return found->second;
}
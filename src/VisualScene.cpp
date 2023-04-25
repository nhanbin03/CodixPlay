#include "VisualScene.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "Helper.h"

VisualScene::VisualScene() {
}

VisualScene::~VisualScene() {
}

VisualScene VisualScene::transitionScene(const VisualScene& fromScene,
                                         const VisualScene& toScene, float time,
                                         float totalTime) {
    VisualScene ret;

    transitionBlock(fromScene, toScene, time, totalTime, ret);
    transitionNode(fromScene, toScene, time, totalTime, ret);
    transitionArrow(fromScene, toScene, time, totalTime, ret);
    transitionLabel(fromScene, toScene, time, totalTime, ret);

    return ret;
}

// Priority: label -> nodes/arrays -> arrow
void VisualScene::draw() {
    for (auto obj : mBlockMap) {
        obj.second.draw();
    }
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

int VisualScene::createBlock() {
    SquareNode newObject;

    int objectID = newObject.getObjectID();
    auto insertStatus = mBlockMap.emplace(objectID, newObject);

    assert(insertStatus.second == true);

    return objectID;
}

void VisualScene::moveBlock(int blockID, Vector2 position) {
    getBlock(blockID).setPosition(position);
}

void VisualScene::moveBlockDelta(int blockID, Vector2 position) {
    SquareNode& obj = getBlock(blockID);
    obj.setPosition(obj.getPosition() + position);
}

void VisualScene::colorBlock(int blockID, Color color) {
    SquareNode& obj = getBlock(blockID);
    obj.setBorderColor(color);
    highlightBlock(blockID);
}

void VisualScene::highlightBlock(int blockID) {
    SquareNode& obj = getBlock(blockID);
    obj.setColor(obj.getBorderColor());
    obj.setValueColor(AppColor::BACKGROUND_2);
}

void VisualScene::unhighlightBlock(int blockID) {
    SquareNode& obj = getBlock(blockID);
    obj.setColor(AppColor::BACKGROUND_2);
    obj.setValueColor(obj.getBorderColor());
}

void VisualScene::setValueBlock(int blockID, int value) {
    getBlock(blockID).setValue(value);
}

void VisualScene::removeValueBlock(int blockID) {
    getBlock(blockID).removeValue();
}

void VisualScene::removeBlock(int blockID) {
    mBlockMap.erase(blockID);
}

Vector2 VisualScene::getBlockPosition(int blockID) const {
    return getBlock(blockID).getPosition();
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

void VisualScene::moveNodeDelta(int nodeID, Vector2 position) {
    CircleNode& obj = getNode(nodeID);
    obj.setPosition(obj.getPosition() + position);
}

void VisualScene::colorNode(int nodeID, Color color) {
    CircleNode& node = getNode(nodeID);
    node.setBorderColor(color);
    highlightNode(nodeID);
}

void VisualScene::highlightNode(int nodeID) {
    CircleNode& node = getNode(nodeID);
    node.setColor(node.getBorderColor());
    node.setValueColor(AppColor::BACKGROUND_2);
}

void VisualScene::unhighlightNode(int nodeID) {
    CircleNode& node = getNode(nodeID);
    node.setColor(AppColor::BACKGROUND_2);
    node.setValueColor(node.getBorderColor());
}

void VisualScene::updateNode(int nodeID, int value) {
    getNode(nodeID).setValue(value);
}

void VisualScene::removeNode(int nodeID) {
    mNodeMap.erase(nodeID);
}

Vector2 VisualScene::getNodePosition(int nodeID) const {
    return getNode(nodeID).getPosition();
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

int VisualScene::createCircularArrow(Vector2 source, Vector2 destination) {
    Arrow newObject(true);
    newObject.setSource(source);
    newObject.setDestination(destination);

    int objectID = newObject.getObjectID();
    auto insertStatus = mArrowMap.emplace(objectID, newObject);

    assert(insertStatus.second == true);

    return objectID;
}

int VisualScene::createOffsetArrow(Vector2 source, Vector2 destination) {
    Arrow newObject;
    newObject.setSource(source);
    newObject.setDestination(destination);
    newObject.setSideOffset(7);

    int objectID = newObject.getObjectID();
    auto insertStatus = mArrowMap.emplace(objectID, newObject);

    assert(insertStatus.second == true);

    return objectID;
}

void VisualScene::moveArrowSource(int arrowID, Vector2 source) {
    Arrow& obj = getArrow(arrowID);
    obj.setSource(source);
}

void VisualScene::moveArrowDestination(int arrowID, Vector2 destination) {
    Arrow& obj = getArrow(arrowID);
    obj.setDestination(destination);
}

void VisualScene::moveArrowDelta(int arrowID, Vector2 source,
                                 Vector2 destination) {
    Arrow& obj = getArrow(arrowID);
    obj.setSource(obj.getSource() + source);
    obj.setDestination(obj.getDestination() + destination);
}

void VisualScene::removeArrow(int arrowID) {
    mArrowMap.erase(arrowID);
}

int VisualScene::createLabel(const std::string text, Vector2 position) {
    Label newObject(text);
    newObject.setPosition(position);

    int objectID = newObject.getObjectID();
    auto insertStatus = mLabelMap.insert(std::make_pair(objectID, newObject));
    assert(insertStatus.second == true);

    return objectID;
}

int VisualScene::createNodeLabel(const std::string text, int idAttached) {
    Label newObject(text);
    Vector2 position = mNodeMap[idAttached].getPosition();
    position.y += VisualObject::ELEMENT_SIZE;
    newObject.setPosition(position);

    int objectID = newObject.getObjectID();
    auto insertStatus = mLabelMap.emplace(objectID, newObject);
    return objectID;
}

void VisualScene::setSizeLabel(int labelID, int size) {
    getLabel(labelID).setSize(size);
}

void VisualScene::moveLabel(int labelID, Vector2 position) {
    getLabel(labelID).setPosition(position);
}

void VisualScene::attachNodeLabel(int labelID, int idAttached) {
    if (labelID == -1)
        return;
    getLabel(labelID).setPosition(getNode(idAttached).getPosition()
                                  + Vector2({0, VisualObject::ELEMENT_SIZE}));
}

void VisualScene::updateLabel(int labelID, const std::string text) {
    getLabel(labelID).setText(text);
}

void VisualScene::removeLabel(int labelID) {
    mLabelMap.erase(labelID);
}

SquareNode& VisualScene::getBlock(int blockID) {
    auto found = mBlockMap.find(blockID);
    assert(found != mBlockMap.end());

    return found->second;
}

const SquareNode& VisualScene::getBlock(int blockID) const {
    auto found = mBlockMap.find(blockID);
    assert(found != mBlockMap.end());

    return found->second;
}

CircleNode& VisualScene::getNode(int nodeID) {
    auto found = mNodeMap.find(nodeID);
    assert(found != mNodeMap.end());

    return found->second;
}

const CircleNode& VisualScene::getNode(int nodeID) const {
    auto found = mNodeMap.find(nodeID);
    assert(found != mNodeMap.end());

    return found->second;
}

Arrow& VisualScene::getArrow(int arrowID) {
    auto found = mArrowMap.find(arrowID);
    assert(found != mArrowMap.end());

    return found->second;
}

const Arrow& VisualScene::getArrow(int arrowID) const {
    auto found = mArrowMap.find(arrowID);
    assert(found != mArrowMap.end());

    return found->second;
}

Label& VisualScene::getLabel(int labelID) {
    auto found = mLabelMap.find(labelID);
    assert(found != mLabelMap.end());

    return found->second;
}

const Label& VisualScene::getLabel(int labelID) const {
    auto found = mLabelMap.find(labelID);
    assert(found != mLabelMap.end());

    return found->second;
}

float VisualScene::easeInOut(float from, float to, float time,
                             float totalTime) {
    return EaseCircInOut(time, from, to - from, totalTime);
}

Color VisualScene::easeInOutColor(Color fromColor, Color toColor, float time,
                                  float totalTime) {
    Color newColor;
    newColor.r = easeInOut(fromColor.r, toColor.r, time, totalTime);
    newColor.g = easeInOut(fromColor.g, toColor.g, time, totalTime);
    newColor.b = easeInOut(fromColor.b, toColor.b, time, totalTime);
    newColor.a = easeInOut(fromColor.a, toColor.a, time, totalTime);
    return newColor;
}

void VisualScene::transitionBlock(const VisualScene& fromScene,
                                  const VisualScene& toScene, float time,
                                  float totalTime, VisualScene& visualScene) {
    std::set<int> idSet;

    for (const auto& p : fromScene.mBlockMap) {
        idSet.insert(p.first);
    }
    for (const auto& p : toScene.mBlockMap) {
        idSet.insert(p.first);
    }

    for (int id : idSet) {
        SquareNode from, to;

        auto fromFound = fromScene.mBlockMap.find(id);
        auto toFound = toScene.mBlockMap.find(id);

        assert(fromFound != fromScene.mBlockMap.end()
               || toFound != toScene.mBlockMap.end());

        if (fromFound != fromScene.mBlockMap.end()) {
            from = fromFound->second;
        }
        if (toFound != toScene.mBlockMap.end()) {
            to = toFound->second;
        }
        if (fromFound == fromScene.mBlockMap.end()) {
            from.setPosition(to.getPosition());
            from.setScale(0);
            if (to.hasValue())
                from.setValue(to.getValue());
            from.setColor(to.getColor());
            from.setBorderColor(to.getBorderColor());
            from.setValueColor(to.getValueColor());
            from.setTransparency(to.getTransparency());
        }
        if (toFound == toScene.mBlockMap.end()) {
            to.setPosition(from.getPosition());
            to.setScale(0);
            if (from.hasValue())
                to.setValue(from.getValue());
            to.setColor(from.getColor());
            to.setBorderColor(from.getBorderColor());
            to.setValueColor(from.getValueColor());
            to.setTransparency(to.getTransparency());
        }

        SquareNode newObject = to;
        int objectID = newObject.getObjectID();

        // Animate position
        Vector2 newPos;
        newPos.x = easeInOut(from.getPosition().x, to.getPosition().x, time,
                             totalTime);
        newPos.y = easeInOut(from.getPosition().y, to.getPosition().y, time,
                             totalTime);
        newObject.setPosition(newPos);

        // Animate scale
        newObject.setScale(
            easeInOut(from.getScale(), to.getScale(), time, totalTime));

        // Animate value
        if (from.hasValue() && to.hasValue()) {
            newObject.setValue(
                easeInOut(from.getValue(), to.getValue(), time, totalTime));
            newObject.setValueColor(easeInOutColor(
                from.getValueColor(), to.getValueColor(), time, totalTime));
        } else {
            // Fading effect
            Color fromColor, toColor;
            int value;
            if (from.hasValue()) {
                fromColor = from.getValueColor();
                toColor = to.getColor();
                value = from.getValue();
            }
            if (to.hasValue()) {
                fromColor = from.getColor();
                toColor = to.getValueColor();
                value = to.getValue();
            }
            if (from.hasValue() || to.hasValue())
                newObject.setValue(value);
            newObject.setValueColor(
                easeInOutColor(fromColor, toColor, time, totalTime));
        }

        // Animate color
        newObject.setColor(
            easeInOutColor(from.getColor(), to.getColor(), time, totalTime));
        newObject.setBorderColor(easeInOutColor(
            from.getBorderColor(), to.getBorderColor(), time, totalTime));
        newObject.setTransparency(easeInOut(
            from.getTransparency(), to.getTransparency(), time, totalTime));

        auto insertStatus = visualScene.mBlockMap.emplace(objectID, newObject);
        assert(insertStatus.second == true);
    }
}

void VisualScene::transitionNode(const VisualScene& fromScene,
                                 const VisualScene& toScene, float time,
                                 float totalTime, VisualScene& visualScene) {
    std::set<int> idSet;

    for (const auto& p : fromScene.mNodeMap) {
        idSet.insert(p.first);
    }
    for (const auto& p : toScene.mNodeMap) {
        idSet.insert(p.first);
    }

    for (int id : idSet) {
        CircleNode from, to;

        auto fromFound = fromScene.mNodeMap.find(id);
        auto toFound = toScene.mNodeMap.find(id);

        assert(fromFound != fromScene.mNodeMap.end()
               || toFound != toScene.mNodeMap.end());

        if (fromFound != fromScene.mNodeMap.end()) {
            from = fromFound->second;
        }
        if (toFound != toScene.mNodeMap.end()) {
            to = toFound->second;
        }
        if (fromFound == fromScene.mNodeMap.end()) {
            from.setPosition(to.getPosition());
            from.setScale(0);
            from.setValue(to.getValue());
            from.setColor(to.getColor());
            from.setBorderColor(to.getBorderColor());
            from.setValueColor(to.getValueColor());
        }
        if (toFound == toScene.mNodeMap.end()) {
            to.setPosition(from.getPosition());
            to.setScale(0);
            to.setValue(from.getValue());
            to.setColor(from.getColor());
            to.setBorderColor(from.getBorderColor());
            to.setValueColor(from.getValueColor());
        }

        CircleNode newObject = to;
        int objectID = newObject.getObjectID();

        // Animate position
        Vector2 newPos;
        newPos.x = easeInOut(from.getPosition().x, to.getPosition().x, time,
                             totalTime);
        newPos.y = easeInOut(from.getPosition().y, to.getPosition().y, time,
                             totalTime);
        newObject.setPosition(newPos);

        // Animate scale
        newObject.setScale(
            easeInOut(from.getScale(), to.getScale(), time, totalTime));

        // Animate value
        newObject.setValue(
            easeInOut(from.getValue(), to.getValue(), time, totalTime));

        // Animate color
        newObject.setColor(
            easeInOutColor(from.getColor(), to.getColor(), time, totalTime));
        newObject.setBorderColor(easeInOutColor(
            from.getBorderColor(), to.getBorderColor(), time, totalTime));
        newObject.setValueColor(easeInOutColor(
            from.getValueColor(), to.getValueColor(), time, totalTime));

        auto insertStatus = visualScene.mNodeMap.emplace(objectID, newObject);
        assert(insertStatus.second == true);
    }
}

void VisualScene::transitionArrow(const VisualScene& fromScene,
                                  const VisualScene& toScene, float time,
                                  float totalTime, VisualScene& visualScene) {
    std::set<int> idSet;

    for (const auto& p : fromScene.mArrowMap) {
        idSet.insert(p.first);
    }
    for (const auto& p : toScene.mArrowMap) {
        idSet.insert(p.first);
    }

    for (int id : idSet) {
        Arrow from, to;

        auto fromFound = fromScene.mArrowMap.find(id);
        auto toFound = toScene.mArrowMap.find(id);

        assert(fromFound != fromScene.mArrowMap.end()
               || toFound != toScene.mArrowMap.end());

        if (fromFound != fromScene.mArrowMap.end()) {
            from = fromFound->second;
        }
        if (toFound != toScene.mArrowMap.end()) {
            to = toFound->second;
        }
        if (fromFound == fromScene.mArrowMap.end()) {
            from.setSource(to.getSource());
            from.setDestination(to.getDestination());
            from.setScale(0);
            from.setCircular(to.isCircular());
            from.setSideOffset(to.getSideOffset());
        }
        if (toFound == toScene.mArrowMap.end()) {
            to.setSource(from.getSource());
            to.setDestination(from.getDestination());
            to.setScale(0);
            to.setCircular(from.isCircular());
            to.setSideOffset(from.getSideOffset());
        }

        Arrow newObject = to;
        int objectID = newObject.getObjectID();

        // Animate source
        Vector2 newSource;
        newSource.x =
            easeInOut(from.getSource().x, to.getSource().x, time, totalTime);
        newSource.y =
            easeInOut(from.getSource().y, to.getSource().y, time, totalTime);
        newObject.setSource(newSource);

        // Animate destination
        Vector2 newDestination;
        newDestination.x = easeInOut(from.getDestination().x,
                                     to.getDestination().x, time, totalTime);
        newDestination.y = easeInOut(from.getDestination().y,
                                     to.getDestination().y, time, totalTime);
        newObject.setDestination(newDestination);

        // Animate scale
        newObject.setScale(
            easeInOut(from.getScale(), to.getScale(), time, totalTime));

        auto insertStatus = visualScene.mArrowMap.emplace(objectID, newObject);
        assert(insertStatus.second == true);
    }
}

void VisualScene::transitionLabel(const VisualScene& fromScene,
                                  const VisualScene& toScene, float time,
                                  float totalTime, VisualScene& visualScene) {
    std::set<int> idSet;

    for (const auto& p : fromScene.mLabelMap) {
        idSet.insert(p.first);
    }
    for (const auto& p : toScene.mLabelMap) {
        idSet.insert(p.first);
    }

    for (int id : idSet) {
        Label from, to;

        auto fromFound = fromScene.mLabelMap.find(id);
        auto toFound = toScene.mLabelMap.find(id);

        assert(fromFound != fromScene.mLabelMap.end()
               || toFound != toScene.mLabelMap.end());

        if (fromFound != fromScene.mLabelMap.end()) {
            from = fromFound->second;
        }
        if (toFound != toScene.mLabelMap.end()) {
            to = toFound->second;
        }
        if (fromFound == fromScene.mLabelMap.end()) {
            from.setPosition(to.getPosition());
            from.setScale(0);
            from.setText("");
        }
        if (toFound == toScene.mLabelMap.end()) {
            to.setPosition(from.getPosition());
            to.setScale(0);
            to.setText("");
        }

        Label newObject = to;
        int objectID = newObject.getObjectID();

        // Animate position
        Vector2 newPos;
        newPos.x = easeInOut(from.getPosition().x, to.getPosition().x, time,
                             totalTime);
        newPos.y = easeInOut(from.getPosition().y, to.getPosition().y, time,
                             totalTime);
        newObject.setPosition(newPos);

        // Animate scale
        newObject.setScale(
            easeInOut(from.getScale(), to.getScale(), time, totalTime));

        auto insertStatus = visualScene.mLabelMap.emplace(objectID, newObject);
        assert(insertStatus.second == true);
    }
}
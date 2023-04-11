#include "Visualization.h"

#include <iostream>

Visualization::Visualization(VisualScene initScene)
: mSceneTrack({initScene})
, mControlBar(mSceneTrack, mDisplayingScene) {
    mDisplayingScene = initScene;
}

Visualization::~Visualization() {
}

void Visualization::update(float dt) {
    mControlBar.update(dt);
}

void Visualization::draw() {
    mDisplayingScene.draw();
    mControlBar.draw();
}

void Visualization::reset(VisualScene initScene) {
    mSceneTrack.clear();
    mSceneTrack.push_back(initScene);
    mDisplayingScene = initScene;
}

void Visualization::createNewScene() {
    mSceneTrack.push_back(mSceneTrack.back());
}

VisualScene Visualization::getLastScene() const {
    return mSceneTrack.back();
}

int Visualization::createNode(int value) {
    return mSceneTrack.back().createNode(value);
}

void Visualization::moveNode(int nodeID, Vector2 position) {
    mSceneTrack.back().moveNode(nodeID, position);
}

void Visualization::colorNode(int nodeID, Color color) {
    mSceneTrack.back().colorNode(nodeID, color);
}

void Visualization::colorValueNode(int nodeID, Color color) {
    mSceneTrack.back().colorValueNode(nodeID, color);
}

void Visualization::updateNode(int nodeID, int value) {
    mSceneTrack.back().updateNode(nodeID, value);
}

void Visualization::removeNode(int nodeID) {
    mSceneTrack.back().removeNode(nodeID);
}

Vector2 Visualization::getNodePosition(int nodeID) {
    return mSceneTrack.back().getNodePosition(nodeID);
}

int Visualization::createArrow(Vector2 source, Vector2 destination) {
    return mSceneTrack.back().createArrow(source, destination);
}

void Visualization::removeArrow(int arrowID) {
    mSceneTrack.back().removeArrow(arrowID);
}

int Visualization::createLabel(const std::string text, Vector2 position) {
    return mSceneTrack.back().createLabel(text, position);
}

int Visualization::createNodeLabel(const std::string text, int idAttached) {
    return mSceneTrack.back().createNodeLabel(text, idAttached);
}

void Visualization::moveLabel(int labelID, Vector2 position) {
    mSceneTrack.back().moveLabel(labelID, position);
}

void Visualization::updateLabel(int labelID, const std::string text) {
    mSceneTrack.back().updateLabel(labelID, text);
}

void Visualization::removeLabel(int labelID) {
    mSceneTrack.back().removeLabel(labelID);
}

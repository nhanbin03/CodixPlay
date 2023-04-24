#include "Visualization.h"

#include <iostream>

Visualization::Visualization()
: mSceneTrack({VisualScene()})
, mControlBar(mSceneTrack, mDisplayingScene) {
    mDisplayingScene = mSceneTrack.front();
}

Visualization::~Visualization() {
}

void Visualization::update(float dt) {
    mControlBar.update(dt);
    mCodeHighlighter.setTracker(mControlBar.getTracker());
}

void Visualization::draw() {
    mDisplayingScene.draw();
    mControlBar.draw();
    mCodeHighlighter.draw();
}

void Visualization::reset(VisualScene initScene) {
    mSceneTrack.clear();
    mSceneTrack.push_back(initScene);
    mControlBar.reset();
    mCodeHighlighter.reset();
}

void Visualization::createNewScene() {
    mSceneTrack.push_back(mSceneTrack.back());
}

VisualScene Visualization::getLastScene() const {
    return mSceneTrack.back();
}

int Visualization::createBlock() {
    return mSceneTrack.back().createBlock();
}

void Visualization::moveBlock(int blockID, Vector2 position) {
    mSceneTrack.back().moveBlock(blockID, position);
}

void Visualization::moveBlockDelta(int blockID, Vector2 position) {
    mSceneTrack.back().moveBlockDelta(blockID, position);
}

void Visualization::colorBlock(int blockID, Color color) {
    mSceneTrack.back().colorBlock(blockID, color);
}

void Visualization::highlightBlock(int blockID) {
    mSceneTrack.back().highlightBlock(blockID);
}

void Visualization::unhighlightBlock(int blockID) {
    mSceneTrack.back().unhighlightBlock(blockID);
}

void Visualization::setValueBlock(int blockID, int value) {
    mSceneTrack.back().setValueBlock(blockID, value);
}

void Visualization::removeValueBlock(int blockID) {
    mSceneTrack.back().removeValueBlock(blockID);
}

void Visualization::removeBlock(int blockID) {
    mSceneTrack.back().removeBlock(blockID);
}

Vector2 Visualization::getBlockPosition(int blockID) const {
    return mSceneTrack.back().getBlockPosition(blockID);
}

int Visualization::createNode(int value) {
    return mSceneTrack.back().createNode(value);
}

void Visualization::moveNode(int nodeID, Vector2 position) {
    mSceneTrack.back().moveNode(nodeID, position);
}

void Visualization::moveNodeDelta(int nodeID, Vector2 position) {
    mSceneTrack.back().moveNodeDelta(nodeID, position);
}

void Visualization::colorNode(int nodeID, Color color) {
    mSceneTrack.back().colorNode(nodeID, color);
}

void Visualization::highlightNode(int nodeID) {
    mSceneTrack.back().highlightNode(nodeID);
}

void Visualization::unhighlightNode(int nodeID) {
    mSceneTrack.back().unhighlightNode(nodeID);
}

void Visualization::updateNode(int nodeID, int value) {
    mSceneTrack.back().updateNode(nodeID, value);
}

void Visualization::removeNode(int nodeID) {
    mSceneTrack.back().removeNode(nodeID);
}

Vector2 Visualization::getNodePosition(int nodeID) const {
    return mSceneTrack.back().getNodePosition(nodeID);
}

int Visualization::createArrow(Vector2 source, Vector2 destination) {
    return mSceneTrack.back().createArrow(source, destination);
}

int Visualization::createCircularArrow(Vector2 source, Vector2 destination) {
    return mSceneTrack.back().createCircularArrow(source, destination);
}

int Visualization::createOffsetArrow(Vector2 source, Vector2 destination) {
    return mSceneTrack.back().createOffsetArrow(source, destination);
}

void Visualization::moveArrowSource(int arrowID, Vector2 source) {
    mSceneTrack.back().moveArrowSource(arrowID, source);
}

void Visualization::moveArrowDestination(int arrowID, Vector2 destination) {
    mSceneTrack.back().moveArrowDestination(arrowID, destination);
}

void Visualization::moveArrowDelta(int arrowID, Vector2 source,
                                   Vector2 destination) {
    mSceneTrack.back().moveArrowDelta(arrowID, source, destination);
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

void Visualization::setSizeLabel(int labelID, int size) {
    mSceneTrack.back().setSizeLabel(labelID, size);
}

void Visualization::moveLabel(int labelID, Vector2 position) {
    mSceneTrack.back().moveLabel(labelID, position);
}

void Visualization::attachNodeLabel(int labelID, int idAttached) {
    mSceneTrack.back().attachNodeLabel(labelID, idAttached);
}

void Visualization::updateLabel(int labelID, const std::string text) {
    mSceneTrack.back().updateLabel(labelID, text);
}

void Visualization::removeLabel(int labelID) {
    mSceneTrack.back().removeLabel(labelID);
}

void Visualization::addCode(std::string code) {
    mCodeHighlighter.addCode(code);
}

void Visualization::highlightCode(std::vector<int> lines) {
    mCodeHighlighter.highlightCode(lines);
}

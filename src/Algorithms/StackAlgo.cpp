#include "StackAlgo.h"

#include "../Helper.h"

#include <cassert>
#include <iostream>

StackAlgo::StackAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void StackAlgo::push(int value) {
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);");
    mVisualization.addCode("node->next = head;");
    mVisualization.addCode("head = node");

    // New scene
    newScene({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.moveNode(node->id,
                            STARTING_POSITION + (Vector2){0, SPACING});
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    assignNodePtr(node, node, 3, "node");

    if (mDSHead == nullptr) {
        // New scene
        newScene({1});
    } else {
        // New scene
        newScene({1});
        node->next.node = mDSHead;
        node->next.id = mVisualization.createArrow(
            mVisualization.getNodePosition(node->id),
            mVisualization.getNodePosition(mDSHead->id));
    }

    // New scene
    newScene({2});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 0, "head");

    // New scene
    newScene({});
    relayout();

    // Clean up
    mSceneCleanUp = [this, node]() {
        this->removeReference(node, "node");
    };
}

void StackAlgo::pop() {
}

void StackAlgo::sceneInit() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void StackAlgo::sceneReset() {
    mVisualization.reset();
    mDSHead = nullptr;
}

void StackAlgo::generalCleanUp() {
    for (Node::Ptr cur = mDSHead; cur != nullptr; cur = cur->next.node) {
        mVisualization.colorNode(cur->id, VisualColor::getPrimaryColor());
        mVisualization.unhighlightNode(cur->id);
    }
}

void StackAlgo::relayout() {
    mVisualization.moveNode(mDSHead->id, STARTING_POSITION);
    mVisualization.attachNodeLabel(mDSHead->referencesId, mDSHead->id);
    for (Node::Ptr cur = mDSHead; cur->next.node != nullptr;
         cur = cur->next.node) {
        Node::Ptr nextNode = cur->next.node;
        mVisualization.moveNode(
            nextNode->id,
            mVisualization.getNodePosition(cur->id) + (Vector2){SPACING, 0});
        mVisualization.moveArrowSource(cur->next.id,
                                       mVisualization.getNodePosition(cur->id));
        mVisualization.moveArrowDestination(
            cur->next.id, mVisualization.getNodePosition(nextNode->id));
        mVisualization.attachNodeLabel(nextNode->referencesId, nextNode->id);
    }
}

void StackAlgo::newScene(std::vector<int> lines) {
    mVisualization.createNewScene();
    mVisualization.highlightCode(lines);
}

void StackAlgo::addReference(Node::Ptr node, int order, std::string reference) {
    if (node == nullptr)
        return;
    node->references[order] = reference;
    if (node->referencesId == -1)
        node->referencesId = mVisualization.createNodeLabel("", node->id);

    mVisualization.updateLabel(node->referencesId, node->referencesText());
}

void StackAlgo::removeReference(Node::Ptr node, std::string reference) {
    assert(node != nullptr);
    for (auto it = node->references.begin(); it != node->references.end();
         it++) {
        if (it->second == reference) {
            node->references.erase(it);
            break;
        }
    }
    mVisualization.updateLabel(node->referencesId, node->referencesText());
}

void StackAlgo::clearReference(Node::Ptr node) {
    node->references.clear();
    if (node->referencesId != -1)
        mVisualization.removeLabel(node->referencesId);
}

void StackAlgo::assignNodePtr(Node::Ptr& from, const Node::Ptr& to, int order,
                              std::string name) {
    if (from != nullptr && from->referencesId != -1) {
        removeReference(from, name);
    }
    from = to;
    addReference(from, order, name);
}

std::string StackAlgo::Node::referencesText() {
    std::string returnText = "";
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it != references.begin())
            returnText += "/";
        returnText += it->second;
    }
    return returnText;
}

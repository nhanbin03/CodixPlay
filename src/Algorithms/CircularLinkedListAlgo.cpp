#include "CircularLinkedListAlgo.h"

#include <cassert>
#include <iostream>

#include "../Helper.h"

CircularLinkedListAlgo::CircularLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void CircularLinkedListAlgo::addHead(int value) {
    mDSSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }
}

void CircularLinkedListAlgo::deleteHead() {
    assert(mDSSize > 0);
    mDSSize--;

    if (mDSSize == 0) {
        deleteSoleNode();
        return;
    }
}

int CircularLinkedListAlgo::getDSSize() const {
    return mDSSize;
}

void CircularLinkedListAlgo::sceneInit() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void CircularLinkedListAlgo::sceneReset() {
    mVisualization.reset();
    mDSHead = nullptr;
    mDSTail = nullptr;
}

void CircularLinkedListAlgo::generalCleanUp() {
    if (mDSHead == nullptr)
        return;
    for (Node::Ptr cur = mDSHead;; cur = cur->next.node) {
        mVisualization.colorNode(cur->id, VisualColor::getPrimaryColor());
        mVisualization.unhighlightNode(cur->id);
        if (cur == mDSTail)
            break;
    }
}

void CircularLinkedListAlgo::addSoleNode(int value) {
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("head = node, tail = node;");     // 1
    mVisualization.addCode("head->next = head;");            // 2

    // New scene
    newScene({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION);
    assignNodePtr(node, node, 3, "node");

    // New scene
    newScene({1});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");
    assignNodePtr(mDSTail, node, 2, "tail");

    // New scene
    newScene({2});
    mDSHead->next.id = mVisualization.createCircularArrow(
        mVisualization.getNodePosition(mDSHead->id),
        mVisualization.getNodePosition(mDSHead->id));

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void CircularLinkedListAlgo::deleteSoleNode() {
    sceneInit();

    mVisualization.addCode("Node* tmp = head;");               // 0
    mVisualization.addCode("head = nullptr, tail = nullptr;"); // 1
    mVisualization.addCode("delete tmp;");                     // 2

    // New scene
    newScene({0});
    Node::Ptr tmp;
    assignNodePtr(tmp, mDSHead, 3, "tmp");
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    newScene({1});
    mDSHead = nullptr;
    removeReference(tmp, "head");
    mDSTail = nullptr;
    removeReference(tmp, "tail");

    // New scene
    newScene({2});
    removeReference(tmp, "tmp");
    mVisualization.removeNode(tmp->id);
    mVisualization.removeArrow(tmp->next.id);

    // Clean up

    mSceneCleanUp = []() {};
}

void CircularLinkedListAlgo::relayout() {
    if (mDSHead == nullptr)
        return;
    mVisualization.moveNode(mDSHead->id, STARTING_POSITION);
    mVisualization.attachNodeLabel(mDSHead->referencesId, mDSHead->id);

    for (Node::Ptr cur = mDSHead; cur != mDSTail; cur = cur->next.node) {
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
    mVisualization.moveArrowSource(mDSTail->next.id,
                                   mVisualization.getNodePosition(mDSHead->id));
    mVisualization.moveArrowDestination(
        mDSTail->next.id, mVisualization.getNodePosition(mDSTail->id));
}

void CircularLinkedListAlgo::newScene(std::vector<int> lines) {
    mVisualization.createNewScene();
    mVisualization.highlightCode(lines);
}

void CircularLinkedListAlgo::addReference(Node::Ptr node, int order,
                                          std::string reference) {
    if (node == nullptr)
        return;
    node->references[order] = reference;
    if (node->referencesId == -1)
        node->referencesId = mVisualization.createNodeLabel("", node->id);

    mVisualization.updateLabel(node->referencesId, node->referencesText());
}

void CircularLinkedListAlgo::removeReference(Node::Ptr node,
                                             std::string reference) {
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

void CircularLinkedListAlgo::clearReference(Node::Ptr node) {
    node->references.clear();
    if (node->referencesId != -1)
        mVisualization.removeLabel(node->referencesId);
}

void CircularLinkedListAlgo::assignNodePtr(Node::Ptr& from, const Node::Ptr& to,
                                           int order, std::string name) {
    if (from != nullptr && from->referencesId != -1) {
        removeReference(from, name);
    }
    from = to;
    addReference(from, order, name);
}

std::string CircularLinkedListAlgo::Node::referencesText() {
    std::string returnText = "";
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it != references.begin())
            returnText += "/";
        returnText += it->second;
    }
    return returnText;
}
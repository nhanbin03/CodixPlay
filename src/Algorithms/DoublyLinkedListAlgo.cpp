#include "DoublyLinkedListAlgo.h"

#include <cassert>
#include <iostream>

#include "../Helper.h"

DoublyLinkedListAlgo::DoublyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void DoublyLinkedListAlgo::addFirst(int value) {
    mDSSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }
}

void DoublyLinkedListAlgo::deleteFirst() {
    assert(mDSSize > 0);
    mDSSize--;

    if (mDSSize == 0) {
        deleteSoleNode();
        return;
    }
}

int DoublyLinkedListAlgo::getDSSize() const {
    return mDSSize;
}

void DoublyLinkedListAlgo::sceneInit() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void DoublyLinkedListAlgo::sceneReset() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    mVisualization.reset();
    mDSHead = nullptr;
    mDSTail = nullptr;
}

void DoublyLinkedListAlgo::generalCleanUp() {
    for (Node::Ptr cur = mDSHead; cur != nullptr; cur = cur->next.node) {
        mVisualization.colorNode(cur->id, VisualColor::getPrimaryColor());
        mVisualization.unhighlightNode(cur->id);
    }
}

void DoublyLinkedListAlgo::assignNodePtr(Node::Ptr& from, const Node::Ptr& to,
                                         int order, std::string name) {
    if (from != nullptr && from->referencesId != -1) {
        removeReference(from, name);
    }
    from = to;
    addReference(from, order, name);
}

void DoublyLinkedListAlgo::relayout() {
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
        mVisualization.moveArrowSource(
            nextNode->prev.id, mVisualization.getNodePosition(nextNode->id));
        mVisualization.moveArrowDestination(
            nextNode->prev.id, mVisualization.getNodePosition(cur->id));
        mVisualization.attachNodeLabel(nextNode->referencesId, nextNode->id);
    }
}

void DoublyLinkedListAlgo::addSoleNode(int value) {
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("head = node, tail = node;");     // 1

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

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void DoublyLinkedListAlgo::deleteSoleNode() {
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

    // Clean up

    mSceneCleanUp = []() {};
}

void DoublyLinkedListAlgo::newScene(std::vector<int> lines) {
    mVisualization.createNewScene();
    mVisualization.highlightCode(lines);
}

void DoublyLinkedListAlgo::addReference(Node::Ptr node, int order,
                                        std::string reference) {
    if (node == nullptr)
        return;
    node->references[order] = reference;
    if (node->referencesId == -1)
        node->referencesId = mVisualization.createNodeLabel("", node->id);

    mVisualization.updateLabel(node->referencesId, node->referencesText());
}

void DoublyLinkedListAlgo::removeReference(Node::Ptr node,
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

void DoublyLinkedListAlgo::clearReference(Node::Ptr node) {
    node->references.clear();
    if (node->referencesId != -1) {
        mVisualization.removeLabel(node->referencesId);
        node->referencesId = -1;
    }
}

std::string DoublyLinkedListAlgo::Node::referencesText() {
    std::string returnText = "";
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it != references.begin())
            returnText += "/";
        returnText += it->second;
    }
    return returnText;
}

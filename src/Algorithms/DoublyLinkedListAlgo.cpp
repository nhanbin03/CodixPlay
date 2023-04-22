#include "DoublyLinkedListAlgo.h"

#include <cassert>
#include <iostream>

#include "../Helper.h"

DoublyLinkedListAlgo::DoublyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void DoublyLinkedListAlgo::initializeRandomFixSize(int size) {
    std::vector<int> list(size);
    for (auto& element : list) {
        element = rand() % 100;
    }
    initialize(list);
}

void DoublyLinkedListAlgo::initialize(std::vector<int> list) {
    mDSSize = list.size();
    sceneReset();
    if (list.size() == 0)
        return;

    mDSHead = std::make_shared<Node>();
    mDSHead->value = list[0];
    mDSHead->id = mVisualization.createNode(list[0]);
    mVisualization.moveNode(mDSHead->id, STARTING_POSITION);
    assignNodePtr(mDSHead, mDSHead, 1, "head");

    Node::Ptr cur = mDSHead;
    for (int i = 1; i < list.size(); i++) {
        Node::Ptr newNode = std::make_shared<Node>();
        newNode->value = list[i];
        newNode->id = mVisualization.createNode(list[i]);
        newNode->next.node = nullptr;
        mVisualization.moveNode(newNode->id, STARTING_POSITION);

        cur->next.node = newNode;
        cur->next.id = mVisualization.createOffsetArrow(STARTING_POSITION,
                                                        STARTING_POSITION);
        newNode->prev.node = cur;
        newNode->prev.id = mVisualization.createOffsetArrow(STARTING_POSITION,
                                                            STARTING_POSITION);

        cur = cur->next.node;
    }
    assignNodePtr(mDSTail, cur, 2, "tail");

    // New scene
    newScene({});
    relayout();
}

void DoublyLinkedListAlgo::addFirst(int value) {
    mDSSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("node->next = head,");            // 1
    mVisualization.addCode("head->prev = node;");            // 2
    mVisualization.addCode("head = node;");                  // 3

    // New scene
    newScene({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    newScene({1, 2});
    node->next.node = mDSHead;
    node->next.id = mVisualization.createOffsetArrow(
        mVisualization.getNodePosition(node->id),
        mVisualization.getNodePosition(mDSHead->id));
    mDSHead->prev.node = node;
    mDSHead->prev.id = mVisualization.createOffsetArrow(
        mVisualization.getNodePosition(mDSHead->id),
        mVisualization.getNodePosition(node->id));

    // New scene
    newScene({3});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");

    // New scene
    newScene({});
    relayout();

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void DoublyLinkedListAlgo::addLast(int value) {
    mDSSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("tail->next = node,");            // 1
    mVisualization.addCode("node->prev = tail,");            // 2
    mVisualization.addCode("tail = node;");                  // 3

    // New scene
    newScene({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(
        node->id,
        mVisualization.getNodePosition(mDSTail->id) + Vector2{SPACING, 0});
    assignNodePtr(node, node, 3, "node");

    // New scene
    newScene({1, 2});
    mDSTail->next.node = node;
    mDSTail->next.id = mVisualization.createOffsetArrow(
        mVisualization.getNodePosition(mDSTail->id),
        mVisualization.getNodePosition(node->id));
    node->prev.node = mDSTail;
    node->prev.id = mVisualization.createOffsetArrow(
        mVisualization.getNodePosition(node->id),
        mVisualization.getNodePosition(mDSTail->id));

    // New scene
    newScene({3});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSTail, node, 2, "tail");

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void DoublyLinkedListAlgo::deleteFirst() {
    assert(mDSSize > 0);
    mDSSize--;

    if (mDSSize == 0) {
        deleteSoleNode();
        return;
    }
    sceneInit();

    mVisualization.addCode("Node* tmp = head;");     // 0
    mVisualization.addCode("head = head->next;");    // 1
    mVisualization.addCode("head->prev = nullptr;"); // 2
    mVisualization.addCode("delete tmp;");           // 3

    // New scene
    newScene({0});
    Node::Ptr tmp;
    assignNodePtr(tmp, mDSHead, 3, "tmp");
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    newScene({1});
    assignNodePtr(mDSHead, mDSHead->next.node, 1, "head");
    mVisualization.highlightNode(mDSHead->id);

    // New scene
    newScene({2});
    mDSHead->prev.node = nullptr;
    mVisualization.removeArrow(mDSHead->prev.id);

    // New scene
    newScene({3});
    mVisualization.removeArrow(tmp->next.id);

    // New scene
    newScene({3});
    removeReference(tmp, "tmp");
    mVisualization.removeNode(tmp->id);

    // New scene
    newScene({});
    relayout();
    mVisualization.unhighlightNode(mDSHead->id);
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

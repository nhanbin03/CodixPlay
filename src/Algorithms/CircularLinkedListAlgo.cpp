#include "CircularLinkedListAlgo.h"

#include <cassert>
#include <iostream>

#include "../Helper.h"

CircularLinkedListAlgo::CircularLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void CircularLinkedListAlgo::initializeRandomFixSize(int size) {
    std::vector<int> list(size);
    for (auto& element : list) {
        element = rand() % 100;
    }
    initialize(list);
}

void CircularLinkedListAlgo::initialize(std::vector<int> list) {
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
        cur->next.id =
            mVisualization.createArrow(STARTING_POSITION, STARTING_POSITION);
        cur = cur->next.node;
    }
    assignNodePtr(mDSTail, cur, 2, "tail");
    mDSTail->next.id = mVisualization.createCircularArrow(
        mVisualization.getNodePosition(mDSTail->id),
        mVisualization.getNodePosition(mDSHead->id));

    // New scene
    newScene({});
    relayout();
}

void CircularLinkedListAlgo::addHead(int value) {
    mDSSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }

    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("node->next = head;");            // 1
    mVisualization.addCode("head = node;");                  // 2
    mVisualization.addCode("tail->next = node;");            // 3

    // New scene
    newScene({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    newScene({1});
    node->next.node = mDSHead;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(mDSHead->id));

    // New scene
    newScene({2});
    assignNodePtr(mDSHead, node, 1, "head");
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    relayout();
    mVisualization.moveArrowDestination(
        mDSTail->next.id,
        mVisualization.getNodePosition(mDSHead->next.node->id));

    // New scene
    newScene({3});
    mVisualization.moveArrowDestination(
        mDSTail->next.id, mVisualization.getNodePosition(mDSHead->id));

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void CircularLinkedListAlgo::addMiddle(int pos, int value) {
    assert(pos != 0 && pos != mDSSize);

    mDSSize++;

    sceneInit();

    mVisualization.addCode("Node* pre = head;");                 // 0
    mVisualization.addCode("for (int i = 0; i < pos - 1; i++)"); // 1
    mVisualization.addCode("    pre = pre->next;");              // 2
    mVisualization.addCode("Node* aft = pre->next;");            // 3
    mVisualization.addCode("Node* node = new Node(value);");     // 4
    mVisualization.addCode("node->next = aft;");                 // 5
    mVisualization.addCode("pre->next = node;");                 // 6

    // New scene
    newScene({0});
    Node::Ptr pre;
    assignNodePtr(pre, mDSHead, 5, "pre");
    mVisualization.highlightNode(mDSHead->id);

    // New scene
    newScene({1});
    addReference(pre, 0, "0");

    // Loop
    for (int i = 0; i < pos - 1; i++) {
        // New scene
        newScene({2});
        mVisualization.unhighlightNode(pre->id);
        Node::Ptr tmp = pre;
        assignNodePtr(pre, pre->next.node, 5, "pre");
        mVisualization.highlightNode(pre->id);

        // New scene
        newScene({1});
        removeReference(tmp, std::to_string(i));
        addReference(pre, 0, std::to_string(i + 1));
    }

    // New scene
    newScene({3});
    Node::Ptr aft;
    assignNodePtr(aft, pre->next.node, 5, "aft");
    addReference(aft, 0, std::to_string(pos));
    mVisualization.colorNode(aft->id, VisualColor::getTertiaryColor());

    // New scene
    newScene({4});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, mVisualization.getNodePosition(aft->id)
                                          + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    newScene({5});
    node->next.node = aft;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(aft->id));

    // New scene
    newScene({6});
    pre->next.node = node;
    mVisualization.moveArrowDestination(
        pre->next.id, mVisualization.getNodePosition(node->id));

    // New scene
    newScene({});
    mVisualization.unhighlightNode(pre->id);
    removeReference(pre, std::to_string(pos - 1));
    removeReference(pre, "pre");
    mVisualization.colorNode(aft->id, VisualColor::getPrimaryColor());
    mVisualization.unhighlightNode(aft->id);
    removeReference(aft, std::to_string(pos));
    removeReference(aft, "aft");
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    relayout();

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void CircularLinkedListAlgo::deleteHead() {
    assert(mDSSize > 0);
    mDSSize--;

    if (mDSSize == 0) {
        deleteSoleNode();
        return;
    }

    sceneInit();

    mVisualization.addCode("Node* tmp = head;");  // 0
    mVisualization.addCode("head = head->next;"); // 1
    mVisualization.addCode("tail->next = head;"); // 2
    mVisualization.addCode("delete tmp;");        // 3

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
    mVisualization.moveArrowDestination(
        mDSTail->next.id, mVisualization.getNodePosition(mDSHead->id));

    // New scene
    newScene({3});
    removeReference(tmp, "tmp");
    mVisualization.removeArrow(tmp->next.id);
    mVisualization.removeNode(tmp->id);

    // New scene
    newScene({});
    relayout();
    mVisualization.unhighlightNode(mDSHead->id);
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
                                   mVisualization.getNodePosition(mDSTail->id));
    mVisualization.moveArrowDestination(
        mDSTail->next.id, mVisualization.getNodePosition(mDSHead->id));
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
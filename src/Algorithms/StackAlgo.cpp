#include "StackAlgo.h"

#include "../Helper.h"

#include <cassert>
#include <iostream>

StackAlgo::StackAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void StackAlgo::initializeRandomFixSize(int size) {
    std::vector<int> list(size);
    for (auto& element : list) {
        element = rand() % 100;
    }
    initialize(list);
}

void StackAlgo::initialize(std::vector<int> list) {
    mStackSize = list.size();
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

    // New scene
    newScene({});
    relayout();
}

void StackAlgo::push(int value) {
    mStackSize++;

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
    sceneInit();

    mVisualization.addCode("if (isEmpty()) return;"); // 0
    mVisualization.addCode("Node* tmp = head;");      // 1
    mVisualization.addCode("head = head->next");      // 2
    mVisualization.addCode("delete tmp;");            // 3

    if (mDSHead == nullptr) {
        // New scene
        newScene({0});
        return;
    }

    mStackSize--;

    // New scene
    newScene({1});
    Node::Ptr tmp;
    assignNodePtr(tmp, mDSHead, 3, "tmp");
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    newScene({2});
    assignNodePtr(mDSHead, mDSHead->next.node, 1, "head");
    if (mDSHead != nullptr)
        mVisualization.highlightNode(mDSHead->id);

    // New scene
    newScene({3});
    removeReference(tmp, "tmp");
    if (mDSHead != nullptr)
        mVisualization.removeArrow(tmp->next.id);
    mVisualization.removeNode(tmp->id);

    // New scene
    newScene({});
    relayout();
    if (mDSHead != nullptr)
        mVisualization.unhighlightNode(mDSHead->id);
}

void StackAlgo::getTop() {
    sceneInit();

    mVisualization.addCode("if (isEmpty()) return NOT_FOUND;"); // 0
    mVisualization.addCode("return head->value;");              // 1

    if (mDSHead == nullptr) {
        // New scene
        newScene({0});
        return;
    }

    // New scene
    newScene({1});
    mVisualization.colorNode(mDSHead->id, VisualColor::getTertiaryColor());
}

int StackAlgo::getDSSize() const {
    return mStackSize;
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
    if (mDSHead == nullptr)
        return;
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

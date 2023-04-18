#include "SinglyLinkedListAlgo.h"

#include <cassert>
#include <iostream>

#include "../Helper.h"

SinglyLinkedListAlgo::SinglyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void SinglyLinkedListAlgo::addFirst(int value) {
    mListSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }

    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("node.next = head;");             // 1
    mVisualization.addCode("head = node;");                  // 2

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});
    node->next.node = mDSHead;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(mDSHead->id));

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({2});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({});
    relayout();

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void SinglyLinkedListAlgo::addMiddle(int pos, int value) {
    assert(pos != 0 && pos != mListSize);

    mListSize++;

    sceneInit();

    mVisualization.addCode("Node* pre = head;");                 // 0
    mVisualization.addCode("for (int i = 0; i < pos - 1; i++)"); // 1
    mVisualization.addCode("    pre = pre.next;");               // 2
    mVisualization.addCode("Node* aft = pre.next;");             // 3
    mVisualization.addCode("Node* node = new Node(value);");     // 4
    mVisualization.addCode("node.next = aft;");                  // 5
    mVisualization.addCode("pre.next = node;");                  // 6

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr pre;
    assignNodePtr(pre, mDSHead, 5, "pre");
    mVisualization.highlightNode(mDSHead->id);

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});
    addReference(pre, 0, "0");

    // Loop
    for (int i = 0; i < pos - 1; i++) {
        // New scene
        mVisualization.createNewScene();
        mVisualization.highlightCode({2});
        mVisualization.unhighlightNode(pre->id);
        Node::Ptr tmp = pre;
        assignNodePtr(pre, pre->next.node, 5, "pre");
        mVisualization.highlightNode(pre->id);

        // New scene
        mVisualization.createNewScene();
        mVisualization.highlightCode({1});
        removeReference(tmp, std::to_string(i));
        addReference(pre, 0, std::to_string(i + 1));
    }

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({3});
    Node::Ptr aft;
    assignNodePtr(aft, pre->next.node, 5, "aft");
    addReference(aft, 0, std::to_string(pos));
    mVisualization.colorNode(aft->id, VisualColor::getTertiaryColor());

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({4});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, mVisualization.getNodePosition(aft->id)
                                          + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({5});
    node->next.node = aft;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(aft->id));

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({6});
    pre->next.node = node;
    mVisualization.moveArrowDestination(
        pre->next.id, mVisualization.getNodePosition(node->id));

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({});
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

void SinglyLinkedListAlgo::addLast(int value) {
    mListSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("tail.next = node;");             // 1
    mVisualization.addCode("tail = node;");                  // 2

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(
        node->id,
        mVisualization.getNodePosition(mDSTail->id) + Vector2{SPACING, 0});
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});
    mDSTail->next.node = node;
    mDSTail->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(mDSTail->id),
                                   mVisualization.getNodePosition(node->id));

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({2});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSTail, node, 2, "tail");

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void SinglyLinkedListAlgo::deleteFirst() {
    assert(mListSize > 0);
    mListSize--;

    if (mListSize == 0) {
        deleteSoleNode();
        return;
    }

    sceneInit();

    mVisualization.addCode("Node* tmp = head;"); // 0
    mVisualization.addCode("head = head.next;"); // 1
    mVisualization.addCode("delete tmp;");       // 2

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr tmp;
    assignNodePtr(tmp, mDSHead, 3, "tmp");
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});
    assignNodePtr(mDSHead, mDSHead->next.node, 1, "head");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({2});
    removeReference(tmp, "tmp");
    mVisualization.removeArrow(tmp->next.id);
    mVisualization.removeNode(tmp->id);

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({});
    relayout();

    // Clean up
    mSceneCleanUp = []() {};
}

void SinglyLinkedListAlgo::deleteLast() {
    assert(mListSize > 0);
    mListSize--;

    if (mListSize == 0) {
        deleteSoleNode();
        return;
    }

    sceneInit();

    mVisualization.addCode("Node* pre = head, tmp = pre.next;");   // 0
    mVisualization.addCode("while (tmp != tail)");                 // 1
    mVisualization.addCode("    tmp = tmp.next, pre = pre.next;"); // 2
    mVisualization.addCode("pre.next = nullptr;");                 // 3
    mVisualization.addCode("tail = pre;");                         // 4
    mVisualization.addCode("delete tmp;");                         // 5

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr pre, tmp;
    assignNodePtr(pre, mDSHead, 3, "pre");
    assignNodePtr(tmp, mDSHead->next.node, 4, "tmp");
    mVisualization.colorNode(pre->id, VisualColor::getPrimaryColor());
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});

    // Loop
    while (tmp != mDSTail) {
        // New scene
        mVisualization.createNewScene();
        mVisualization.highlightCode({2});
        assignNodePtr(tmp, tmp->next.node, 4, "tmp");
        mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());
        mVisualization.unhighlightNode(pre->id);
        assignNodePtr(pre, pre->next.node, 3, "pre");
        mVisualization.colorNode(pre->id, VisualColor::getPrimaryColor());

        // New scene
        mVisualization.createNewScene();
        mVisualization.highlightCode({1});
    }

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({3});
    mVisualization.removeArrow(pre->next.id);
    pre->next.node = nullptr;

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({4});
    assignNodePtr(mDSTail, pre, 2, "tail");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({5});
    removeReference(tmp, "tmp");
    mVisualization.removeNode(tmp->id);

    // Clean up
    mSceneCleanUp = [pre, this]() {
        this->removeReference(pre, "pre");
    };
}

int SinglyLinkedListAlgo::getDSSize() const {
    return mListSize;
}

void SinglyLinkedListAlgo::sceneInit() {
    mSceneCleanUp();
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void SinglyLinkedListAlgo::generalCleanUp() {
    for (Node::Ptr cur = mDSHead; cur != nullptr; cur = cur->next.node) {
        mVisualization.colorNode(cur->id, VisualColor::getPrimaryColor());
        mVisualization.unhighlightNode(cur->id);
    }
}

void SinglyLinkedListAlgo::assignNodePtr(Node::Ptr& from, const Node::Ptr& to,
                                         int order, std::string name) {
    if (from != nullptr && from->referencesId != -1) {
        removeReference(from, name);
    }
    from = to;
    addReference(from, order, name);
}

void SinglyLinkedListAlgo::relayout() {
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
}

void SinglyLinkedListAlgo::addSoleNode(int value) {
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("head = node, tail = node;");     // 1

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION);
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");
    assignNodePtr(mDSTail, node, 2, "tail");

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void SinglyLinkedListAlgo::deleteSoleNode() {
    sceneInit();

    mVisualization.addCode("Node* tmp = head;");               // 0
    mVisualization.addCode("head = nullptr, tail = nullptr;"); // 1
    mVisualization.addCode("delete tmp;");                     // 2

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({0});
    Node::Ptr tmp;
    assignNodePtr(tmp, mDSHead, 3, "tmp");
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({1});
    mDSHead = nullptr;
    removeReference(tmp, "head");
    mDSTail = nullptr;
    removeReference(tmp, "tail");

    // New scene
    mVisualization.createNewScene();
    mVisualization.highlightCode({2});
    removeReference(tmp, "tmp");
    mVisualization.removeNode(tmp->id);

    // Clean up

    mSceneCleanUp = []() {};
}

void SinglyLinkedListAlgo::addReference(Node::Ptr node, int order,
                                        std::string reference) {
    node->references[order] = reference;
    if (node->referencesId == -1)
        node->referencesId = mVisualization.createNodeLabel("", node->id);

    mVisualization.updateLabel(node->referencesId, node->referencesText());
}

void SinglyLinkedListAlgo::removeReference(Node::Ptr node,
                                           std::string reference) {
    for (auto it = node->references.begin(); it != node->references.end();
         it++) {
        if (it->second == reference) {
            node->references.erase(it);
            break;
        }
    }
    mVisualization.updateLabel(node->referencesId, node->referencesText());
}

std::string SinglyLinkedListAlgo::Node::referencesText() {
    std::string returnText = "";
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it != references.begin())
            returnText += "/";
        returnText += it->second;
    }
    return returnText;
}

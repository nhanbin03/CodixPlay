#include "SinglyLinkedListAlgo.h"

#include <iostream>

#include "../Helper.h"

SinglyLinkedListAlgo::SinglyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void SinglyLinkedListAlgo::addFirst(int value) {
    mListSize++;

    if (mDSHead == nullptr) {
        addInitialNode(value);
        return;
    }

    sceneInit();

    // Node* node = new Node(value);
    // node.next = head;
    // head = node;

    // New scene
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    node->next.node = mDSHead;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(mDSHead->id));

    // New scene
    mVisualization.createNewScene();
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");

    // New scene
    mVisualization.createNewScene();
    relayout();

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
}

void SinglyLinkedListAlgo::addMiddle(int pos, int value) {
    mListSize++;

    sceneInit();

    // Node* pre = head;
    // for (int i = 0; i < pos - 1; i++)
    //    pre = pre.next;
    // Node* aft = pre.next;
    // Node* node = new Node(value);
    // node.next = aft;
    // pre.next = node;

    // New scene
    mVisualization.createNewScene();
    Node::Ptr pre;
    assignNodePtr(pre, mDSHead, 5, "pre");
    mVisualization.highlightNode(mDSHead->id);

    // New scene
    mVisualization.createNewScene();
    addReference(pre, 0, "0");

    // Loop
    for (int i = 0; i < pos - 1; i++) {
        // New scene
        mVisualization.createNewScene();
        mVisualization.unhighlightNode(pre->id);
        Node::Ptr tmp = pre;
        assignNodePtr(pre, pre->next.node, 5, "pre");
        mVisualization.highlightNode(pre->id);

        // New scene
        mVisualization.createNewScene();
        removeReference(tmp, std::to_string(i));
        addReference(pre, 0, std::to_string(i + 1));
    }

    // New scene
    mVisualization.createNewScene();
    Node::Ptr aft;
    assignNodePtr(aft, pre->next.node, 5, "aft");
    addReference(aft, 0, std::to_string(pos));
    mVisualization.colorNode(aft->id, VisualColor::getTertiaryColor());

    // New scene
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, mVisualization.getNodePosition(aft->id)
                                          + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    node->next.node = aft;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(aft->id));

    // New scene
    mVisualization.createNewScene();
    pre->next.node = node;
    mVisualization.removeArrow(pre->next.id);
    pre->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(pre->id),
                                   mVisualization.getNodePosition(node->id));

    // New scene
    mVisualization.createNewScene();
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
        addInitialNode(value);
        return;
    }

    sceneInit();

    // Node* node = new Node(value);
    // tail.next = node;
    // tail = node;

    // New scene
    mVisualization.createNewScene();
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
    mDSTail->next.node = node;
    mDSTail->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(mDSTail->id),
                                   mVisualization.getNodePosition(node->id));

    // New scene
    mVisualization.createNewScene();
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSTail, node, 1, "tail");

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
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

void SinglyLinkedListAlgo::addInitialNode(int value) {
    sceneInit();

    // Node* node = new Node(value);
    // head = node, tail = node;

    // New scene
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION);
    assignNodePtr(node, node, 3, "node");

    // New scene
    mVisualization.createNewScene();
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");
    assignNodePtr(mDSTail, node, 2, "tail");

    // Clean up
    mSceneCleanUp = [node, this]() {
        this->removeReference(node, "node");
    };
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

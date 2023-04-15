#include "SinglyLinkedListAlgo.h"

#include <iostream>

#include "../Helper.h"

SinglyLinkedListAlgo::SinglyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void SinglyLinkedListAlgo::addFirst(int value) {
    if (mListSize == MAX_LIST_SIZE)
        return;
    mListSize++;

    if (mDSHead == nullptr) {
        addInitialNode(value);
        return;
    }

    sceneInit();

    // Node* node = new Node(value);
    // node.next = head;
    // head = node;

    // Scene 1
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION + Vector2{0, SPACING});
    assignNodePtr(node, node, 3, "node");

    // Scene 2
    mVisualization.createNewScene();
    node->next.node = mDSHead;
    node->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(node->id),
                                   mVisualization.getNodePosition(mDSHead->id));

    // Scene 3
    mVisualization.createNewScene();
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");

    // Scene 4
    mVisualization.createNewScene();
    relayout();

    // Clean up
    mSceneCleanUp = [node, this]() {
        node->removeReference("node");
        this->mVisualization.updateLabel(node->referencesId,
                                         node->referencesText());
    };
}

void SinglyLinkedListAlgo::addLast(int value) {
    if (mListSize == MAX_LIST_SIZE)
        return;
    mListSize++;

    if (mDSHead == nullptr) {
        addInitialNode(value);
        return;
    }

    sceneInit();

    // Node* node = new Node(value);
    // tail.next = node;
    // tail = node;

    // Scene 1
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(
        node->id,
        mVisualization.getNodePosition(mDSTail->id) + Vector2{SPACING, 0});
    assignNodePtr(node, node, 3, "node");

    // Scene 2
    mVisualization.createNewScene();
    mDSTail->next.node = node;
    mDSTail->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(mDSTail->id),
                                   mVisualization.getNodePosition(node->id));

    // Scene 3
    mVisualization.createNewScene();
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSTail, node, 1, "tail");

    // Clean up
    mSceneCleanUp = [node, this]() {
        node->removeReference("node");
        this->mVisualization.updateLabel(node->referencesId,
                                         node->referencesText());
    };
}

void SinglyLinkedListAlgo::sceneInit() {
    mSceneCleanUp();
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void SinglyLinkedListAlgo::generalCleanUp() {
    for (Node::Ptr cur = mDSHead; cur != nullptr; cur = cur->next.node) {
        mVisualization.unhighlightNode(cur->id);
    }
}

void SinglyLinkedListAlgo::assignNodePtr(Node::Ptr& from, const Node::Ptr& to,
                                         int order, std::string name) {
    if (from != nullptr && from->referencesId != -1) {
        from->removeReference(name);
        mVisualization.updateLabel(from->referencesId, from->referencesText());
    }

    from = to;
    from->addReference(order, name);

    if (from->referencesId == -1) {
        from->referencesId = mVisualization.createNodeLabel("", from->id);
    }
    mVisualization.updateLabel(from->referencesId, from->referencesText());
}

void SinglyLinkedListAlgo::relayout() {
    mVisualization.moveNode(mDSHead->id, STARTING_POSITION);
    mVisualization.attachNodeLabel(mDSHead->referencesId, mDSHead->id);
    for (Node::Ptr cur = mDSHead; cur != mDSTail; cur = cur->next.node) {
        mVisualization.moveArrowSource(cur->next.id,
                                       mVisualization.getNodePosition(cur->id));
        mVisualization.moveArrowDelta(cur->next.id, {0, 0}, {SPACING, 0});
        mVisualization.moveNodeDelta(cur->next.node->id, {SPACING, 0});
        mVisualization.attachNodeLabel(cur->next.node->referencesId,
                                       cur->next.node->id);
    }
}

void SinglyLinkedListAlgo::addInitialNode(int value) {
    sceneInit();

    // Node* node = new Node(value);
    // head = node, tail = node;

    // Scene 1
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.colorNode(node->id, VisualColor::getSecondaryColor());
    mVisualization.moveNode(node->id, STARTING_POSITION);
    assignNodePtr(node, node, 3, "node");

    // Scene 2
    mVisualization.createNewScene();
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSHead, node, 1, "head");
    assignNodePtr(mDSTail, node, 2, "tail");

    // Scene clean up
    mSceneCleanUp = [node, this]() {
        node->removeReference("node");
        this->mVisualization.updateLabel(node->referencesId,
                                         node->referencesText());
    };
}

void SinglyLinkedListAlgo::Node::addReference(int order,
                                              std::string reference) {
    references[order] = reference;
}

void SinglyLinkedListAlgo::Node::removeReference(std::string reference) {
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it->second == reference) {
            references.erase(it);
            break;
        }
    }
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

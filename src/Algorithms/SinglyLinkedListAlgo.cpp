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

    /// If not empty
    // Node* node = new Node(value);
    // node.next = head;
    // head = node;

    // Scene 1
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
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
    assignNodePtr(mDSHead, node, 1, "head");

    // Scene 4
    mVisualization.createNewScene();
    mVisualization.moveNode(node->id, STARTING_POSITION);
    mVisualization.attachNodeLabel(node->referencesId, node->id);
    for (Node::Ptr cur = mDSHead; cur != mDSTail; cur = cur->next.node) {
        mVisualization.moveArrowSource(cur->next.id,
                                       mVisualization.getNodePosition(cur->id));
        mVisualization.moveArrowDelta(cur->next.id, {0, 0}, {SPACING, 0});
        mVisualization.moveNodeDelta(cur->next.node->id, {SPACING, 0});
        mVisualization.attachNodeLabel(cur->next.node->referencesId,
                                       cur->next.node->id);
    }

    // Clean up
    mSceneCleanUp = [node, this]() {
        node->removeReference("node");
        mVisualization.updateLabel(node->referencesId, node->referencesText());
    };
}

void SinglyLinkedListAlgo::sceneInit() {
    mSceneCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
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

void SinglyLinkedListAlgo::addInitialNode(int value) {
    sceneInit();

    // If empty
    // Node* node = new Node(value);
    // head = node, tail = node;

    // Scene 1
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.moveNode(node->id, STARTING_POSITION);
    assignNodePtr(node, node, 3, "node");

    // Scene 2
    mVisualization.createNewScene();
    assignNodePtr(mDSHead, node, 1, "head");
    assignNodePtr(mDSTail, node, 2, "tail");

    // Scene clean up
    mSceneCleanUp = [node, this]() {
        node->removeReference("node");
        mVisualization.updateLabel(node->referencesId, node->referencesText());
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

#include "SinglyLinkedListAlgo.h"

#include <iostream>

SinglyLinkedListAlgo::SinglyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
}

void SinglyLinkedListAlgo::addFirst(int value) {
    sceneInit();
    // If empty
    // Node* node = new Node(value);
    // head = node, tail = node;
    if (mDSHead == nullptr) {
        // Scene 1
        mVisualization.createNewScene();
        Node::Ptr node = std::make_shared<Node>();
        node->value = value;
        node->id = mVisualization.createNode(value);
        mVisualization.moveNode(node->id, {100, 100});
        assignNodePtr(node, node, 3, "node");

        // Scene 2
        mVisualization.createNewScene();
        assignNodePtr(mDSHead, node, 1, "head");
        assignNodePtr(mDSTail, node, 2, "tail");

        // Scene clean up
        mSceneCleanUp = [node, this]() {
            node->removeReference("node");
            mVisualization.updateLabel(node->referencesId,
                                       node->referencesText());
        };
        return;
    }

    /// If not empty
    // Node* node = new Node(value);
    // node.next = head;
    // head = node;

    // Scene 1
    mVisualization.createNewScene();
    Node::Ptr node = std::make_shared<Node>();
    node->value = value;
    node->id = mVisualization.createNode(value);
    mVisualization.moveNode(node->id, {100, 300});
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
    mVisualization.moveNode(node->id, {100, 100});
    mVisualization.attachNodeLabel(node->referencesId, node->id);
    for (Node::Ptr cur = mDSHead; cur != mDSTail; cur = cur->next.node) {
        mVisualization.moveArrowSource(cur->next.id,
                                       mVisualization.getNodePosition(cur->id));
        mVisualization.moveArrowDelta(cur->next.id, {0, 0}, {200, 0});
        mVisualization.moveNodeDelta(cur->next.node->id, {200, 0});
        if (cur->next.node->referencesId != -1)
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

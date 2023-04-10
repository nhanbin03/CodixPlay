#include "SinglyLinkedListAlgo.h"

#include <iostream>

SinglyLinkedListAlgo::SinglyLinkedListAlgo(Visualization& visualization)
: Algorithm(visualization) {
}

void SinglyLinkedListAlgo::addFirst(int value) {
    sceneInit();
    // If empty
    // Node* node = new Node(value);
    // head = node, tail = node;
    if (mDSHead == nullptr) {
        // Scene 1
        mVisualization.createNewScene();
        Node::Ptr node(new Node());
        node->value = value;
        node->id = mVisualization.createNode(value);
        mVisualization.moveNode(node->id, {100, 100});
        node->referencesId = mVisualization.createNodeLabel("node", node->id);

        // Scene 2
        mVisualization.createNewScene();
        mDSHead = node, mDSTail = node;
        mVisualization.updateLabel(node->referencesId, "head/tail/node");
        return;
    }

    /// If not empty
    // Node* node = new Node(value);
    // node.next = head;
    // head = node;
}

void SinglyLinkedListAlgo::sceneInit() {
    mVisualization.reset();
}

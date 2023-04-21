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
    mDSTail->next.node = mDSHead;
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
    mDSTail->next.node = mDSHead;
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

void CircularLinkedListAlgo::addTail(int value) {
    mDSSize++;

    if (mDSHead == nullptr) {
        addSoleNode(value);
        return;
    }
    sceneInit();

    mVisualization.addCode("Node* node = new Node(value);"); // 0
    mVisualization.addCode("tail->next = node;");            // 1
    mVisualization.addCode("tail = node;");                  // 2
    mVisualization.addCode("tail->next = head;");            // 3

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
    newScene({1});
    mDSTail->next.node = node;
    mVisualization.removeArrow(mDSTail->next.id);
    mDSTail->next.id =
        mVisualization.createArrow(mVisualization.getNodePosition(mDSTail->id),
                                   mVisualization.getNodePosition(node->id));

    // New scene
    newScene({2});
    mVisualization.colorNode(node->id, VisualColor::getPrimaryColor());
    assignNodePtr(mDSTail, node, 2, "tail");

    // New scene
    newScene({3});
    mDSTail->next.node = mDSHead;
    mDSTail->next.id = mVisualization.createCircularArrow(
        mVisualization.getNodePosition(mDSTail->id),
        mVisualization.getNodePosition(mDSHead->id));

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
    mDSTail->next.node = mDSHead;
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

void CircularLinkedListAlgo::deleteMiddle(int pos) {
    assert(0 < pos && pos < mDSSize - 1);
    mDSSize--;

    sceneInit();

    mVisualization.addCode("Node* pre = head;");                 // 0
    mVisualization.addCode("for (int i = 0; i < pos - 1; i++)"); // 1
    mVisualization.addCode("    pre = pre->next;");              // 2
    mVisualization.addCode("Node *tmp = pre->next;");            // 3
    mVisualization.addCode("Node* aft = del->next;");            // 4
    mVisualization.addCode("pre->next = aft;");                  // 5
    mVisualization.addCode("delete del;");                       // 6

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
    Node::Ptr tmp;
    assignNodePtr(tmp, pre->next.node, 5, "tmp");
    addReference(tmp, 0, std::to_string(pos));
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    newScene({4});
    Node::Ptr aft;
    assignNodePtr(aft, tmp->next.node, 5, "aft");
    mVisualization.colorNode(aft->id, VisualColor::getTertiaryColor());

    // New scene
    newScene({5});
    mVisualization.moveNodeDelta(tmp->id, {0, -SPACING});
    mVisualization.moveArrowDelta(tmp->next.id, {0, -SPACING}, {0, 0});
    mVisualization.attachNodeLabel(tmp->referencesId, tmp->id);
    pre->next.node = aft;
    mVisualization.moveArrowDestination(
        pre->next.id, mVisualization.getNodePosition(aft->id));

    // New scene
    newScene({6});
    clearReference(tmp);
    mVisualization.removeNode(tmp->id);
    mVisualization.removeArrow(tmp->next.id);

    // New scene
    newScene({});
    removeReference(pre, std::to_string(pos - 1));
    removeReference(pre, "pre");
    removeReference(aft, "aft");
    mVisualization.colorNode(aft->id, VisualColor::getPrimaryColor());
    mVisualization.unhighlightNode(pre->id);
    mVisualization.unhighlightNode(aft->id);
    relayout();
}

void CircularLinkedListAlgo::deleteTail() {
    assert(mDSSize > 0);
    mDSSize--;

    if (mDSSize == 0) {
        deleteSoleNode();
        return;
    }

    sceneInit();

    mVisualization.addCode("Node* pre = head,");      // 0
    mVisualization.addCode("      tmp = pre->next;"); // 1
    mVisualization.addCode("while (tmp != tail)");    // 2
    mVisualization.addCode("    tmp = tmp->next,");   // 3
    mVisualization.addCode("    pre = pre->next;");   // 4
    mVisualization.addCode("pre->next = nullptr;");   // 5
    mVisualization.addCode("tail = pre;");            // 6
    mVisualization.addCode("delete tmp;");            // 7
    mVisualization.addCode("tail->next = head;");     // 8

    // New scene
    newScene({0, 1});
    Node::Ptr pre, tmp;
    assignNodePtr(pre, mDSHead, 3, "pre");
    assignNodePtr(tmp, mDSHead->next.node, 4, "tmp");
    mVisualization.colorNode(pre->id, VisualColor::getPrimaryColor());
    mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());

    // New scene
    newScene({2});

    // Loop
    while (tmp != mDSTail) {
        // New scene
        newScene({3, 4});
        assignNodePtr(tmp, tmp->next.node, 4, "tmp");
        mVisualization.colorNode(tmp->id, VisualColor::getSecondaryColor());
        mVisualization.unhighlightNode(pre->id);
        assignNodePtr(pre, pre->next.node, 3, "pre");
        mVisualization.colorNode(pre->id, VisualColor::getPrimaryColor());

        // New scene
        newScene({2});
    }

    // New scene
    newScene({5});
    mVisualization.removeArrow(pre->next.id);
    pre->next.node = nullptr;

    // New scene
    newScene({6});
    assignNodePtr(mDSTail, pre, 2, "tail");

    // New scene
    newScene({7});
    removeReference(tmp, "tmp");
    mVisualization.removeNode(tmp->id);
    mVisualization.removeArrow(tmp->next.id);

    // New scene
    newScene({8});
    mDSTail->next.node = mDSHead;
    mDSTail->next.id = mVisualization.createCircularArrow(
        mVisualization.getNodePosition(mDSTail->id),
        mVisualization.getNodePosition(mDSHead->id));

    // New scene
    newScene({});
    removeReference(pre, "pre");
    mVisualization.unhighlightNode(pre->id);
}

void CircularLinkedListAlgo::updateValue(int pos, int value) {
    assert(0 <= pos && pos < mDSSize);

    sceneInit();

    mVisualization.addCode("Node* cur = head;");             // 0
    mVisualization.addCode("for (int i = 0; i < pos; i++)"); // 1
    mVisualization.addCode("    cur = cur->next;");          // 2
    mVisualization.addCode("cur->value");                    // 3

    // New scene
    newScene({0});
    Node::Ptr cur;
    assignNodePtr(cur, mDSHead, 5, "cur");
    mVisualization.highlightNode(cur->id);

    // New scene
    newScene({1});
    addReference(cur, 0, "0");

    // Loop
    for (int i = 0; i < pos; i++) {
        // New scene
        newScene({2});
        mVisualization.unhighlightNode(cur->id);
        Node::Ptr tmp = cur;
        assignNodePtr(cur, cur->next.node, 5, "cur");
        mVisualization.highlightNode(cur->id);

        // New scene
        newScene({1});
        removeReference(tmp, std::to_string(i));
        addReference(cur, 0, std::to_string(i + 1));
    }
    // New scene
    newScene({3});
    mVisualization.updateNode(cur->id, value);
    cur->value = value;

    mSceneCleanUp = [pos, cur, this]() {
        this->removeReference(cur, std::to_string(pos));
        this->removeReference(cur, "cur");
    };
}

void CircularLinkedListAlgo::searchValue(int value) {
    sceneInit();

    mVisualization.addCode("if (isEmpty()) return NOT_FOUND;"); // 0
    mVisualization.addCode("Node* cur = head;");                // 1
    mVisualization.addCode("int index = 0");                    // 2
    mVisualization.addCode("while(cur->value != value) {");     // 3
    mVisualization.addCode("    index++, cur = cur->next;");    // 4
    mVisualization.addCode("    if (cur == head)");             // 5
    mVisualization.addCode("        return NOT_FOUND;");        // 6
    mVisualization.addCode("}");                                // 7
    mVisualization.addCode("return index;");                    // 8

    if (mDSHead == nullptr) {
        // New scene
        newScene({0});
        return;
    }

    // New scene
    newScene({1, 2});
    Node::Ptr cur;
    assignNodePtr(cur, mDSHead, 5, "cur");
    addReference(cur, 0, "0");
    mVisualization.colorNode(cur->id, VisualColor::getSecondaryColor());
    int idx = 0;

    // New scene
    newScene({3});
    mVisualization.unhighlightNode(cur->id);

    // Loop
    while (cur->value != value) {
        // New scene
        newScene({4, 5});
        removeReference(cur, std::to_string(idx));
        idx++;
        assignNodePtr(cur, cur->next.node, 5, "cur");
        addReference(cur, 0, std::to_string(idx));
        mVisualization.colorNode(cur->id, VisualColor::getSecondaryColor());

        if (cur == mDSHead) {
            // New scene
            newScene({5, 6});

            mSceneCleanUp = [this, cur, idx]() {
                this->removeReference(cur, std::to_string(idx));
                this->removeReference(cur, "cur");
            };
            return;
        }

        // New scene
        newScene({3});
        mVisualization.unhighlightNode(cur->id);
    }

    // New scene
    newScene({8});
    mVisualization.colorNode(cur->id, VisualColor::getTertiaryColor());

    // Clean up
    mSceneCleanUp = [this, cur, idx]() {
        this->removeReference(cur, std::to_string(idx));
        this->removeReference(cur, "cur");
    };
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
    mSceneCleanUp();
    mSceneCleanUp = []() {};
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
    mDSHead->next.node = mDSHead;
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
    if (node->referencesId != -1) {
        mVisualization.removeLabel(node->referencesId);
        node->referencesId = -1;
    }
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
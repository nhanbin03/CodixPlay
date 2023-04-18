#ifndef ALGORITHMS_SINGLYLINKEDLISTALGO_H
#define ALGORITHMS_SINGLYLINKEDLISTALGO_H

#include "../Visualization.h"
#include "Algorithm.h"

#include <functional>
#include <memory>
#include <string>

class SinglyLinkedListAlgo : public Algorithm {
public:
    static constexpr int MAX_LIST_SIZE = 7;

public:
    SinglyLinkedListAlgo(Visualization& visualization);

    void initializeRandom();

    void addFirst(int value);
    void addMiddle(int pos, int value);
    void addLast(int value);

    void deleteFirst();
    void deleteMiddle(int pos);
    void deleteLast();

    void updateValue(int pos, int value);

    void searchValue(int value);

    int getDSSize() const;

private:
    class Node {
    public:
        typedef std::shared_ptr<Node> Ptr;

        struct NodePointer {
            Node::Ptr node;
            int id;
        };

    public:
        int value;
        int id;

        NodePointer next;

        int referencesId{-1};
        std::map<int, std::string> references; // pointers pointed to this node
    public:
        std::string referencesText();
    };

private:
    int mListSize{0};

    Node::Ptr mDSHead, mDSTail;

    std::function<void()> mSceneCleanUp;

private:
    void sceneInit();

    void generalCleanUp();

    void assignNodePtr(Node::Ptr& from, const Node::Ptr& to, int order,
                       std::string name);

    void relayout();

    void addSoleNode(int value);
    void deleteSoleNode();

    void addReference(Node::Ptr node, int order, std::string reference);
    void removeReference(Node::Ptr node, std::string reference);
};

#endif // ALGORITHMS_SINGLYLINKEDLISTALGO_H

#ifndef ALGORITHMS_SINGLYLINKEDLISTALGO_H
#define ALGORITHMS_SINGLYLINKEDLISTALGO_H

#include "../Visualization.h"
#include "Algorithm.h"

#include <functional>
#include <memory>
#include <string>

class SinglyLinkedListAlgo : public Algorithm {
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
        void addReference(int order, std::string reference);
        void removeReference(std::string reference);

        std::string referencesText();
    };

private:
    Node::Ptr mDSHead, mDSTail;

    std::function<void()> mSceneCleanUp;

private:
    void sceneInit();

    void assignNodePtr(Node::Ptr& from, const Node::Ptr& to, int order,
                       std::string name);
};

#endif // ALGORITHMS_SINGLYLINKEDLISTALGO_H

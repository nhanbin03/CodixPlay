#ifndef ALGORITHMS_STACKALGO_H
#define ALGORITHMS_STACKALGO_H

#include "../Visualization.h"
#include "Algorithm.h"

#include <functional>
#include <memory>
#include <string>

class StackAlgo : public Algorithm {
public:
    static constexpr int MAX_LIST_SIZE = 7;

public:
    StackAlgo(Visualization& visualization);

    void initializeRandomFixSize(int size);
    void initialize(std::vector<int> list);

    void push(int value);

    void pop();

    void getTop();

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

    Node::Ptr mDSHead;

    std::function<void()> mSceneCleanUp;

private:
    void pushSoleNode(int value);
    void popSoleNode();

    void sceneInit();
    void sceneReset();

    void generalCleanUp();

    void relayout();

    void newScene(std::vector<int> lines);
    void addReference(Node::Ptr node, int order, std::string reference);
    void removeReference(Node::Ptr node, std::string reference);
    void clearReference(Node::Ptr node);
    void assignNodePtr(Node::Ptr& from, const Node::Ptr& to, int order,
                       std::string name);
};

#endif // ALGORITHMS_STACKALGO_H

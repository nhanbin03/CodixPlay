#ifndef ALGORITHMS_QUEUEALGO_H
#define ALGORITHMS_QUEUEALGO_H

#include "../Visualization.h"
#include "Algorithm.h"

#include <functional>
#include <memory>
#include <string>

class QueueAlgo : public Algorithm {
public:
    static constexpr int MAX_DS_SIZE = 7;

public:
    QueueAlgo(Visualization& visualization);

    void initializeRandomFixSize(int size);
    void initialize(std::vector<int> list);

    void enqueue(int value);

    void dequeue();

    void getFront();

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
    int mDSSize{0};

    Node::Ptr mDSHead, mDSTail;

    std::function<void()> mSceneCleanUp;

private:
    void sceneInit();
    void sceneReset();

    void generalCleanUp();

    void addSoleNode(int value);
    void deleteSoleNode();

    void relayout();

    void newScene(std::vector<int> lines);
    void addReference(Node::Ptr node, int order, std::string reference);
    void removeReference(Node::Ptr node, std::string reference);
    void clearReference(Node::Ptr node);
    void assignNodePtr(Node::Ptr& from, const Node::Ptr& to, int order,
                       std::string name);
};

#endif // ALGORITHMS_QUEUEALGO_H

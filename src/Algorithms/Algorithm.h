#ifndef ALGORITHMS_ALGORITHM_H
#define ALGORITHMS_ALGORITHM_H

#include "../Visualization.h"

#include <memory>
#include <string>
#include <vector>

class Algorithm {
public:
    struct Node {
        typedef std::shared_ptr<Node> Ptr;

        struct NodePointer {
            Node::Ptr node;
            int id;
        };

        NodePointer next;

        int referencesId;

        int value;
        int id;
        // TODO: Keep track of labels and arrows, objectize pointers (arrow
        // pointers and label pointers)
    };

public:
    Algorithm(Visualization& visualization);

protected:
    Visualization& mVisualization;
};

#endif // ALGORITHMS_ALGORITHM_H

#ifndef ALGORITHMS_SINGLYLINKEDLISTALGO_H
#define ALGORITHMS_SINGLYLINKEDLISTALGO_H

#include "../Visualization.h"
#include "Algorithm.h"

#include <memory>
#include <string>

class SinglyLinkedListAlgo : public Algorithm {
public:
    SinglyLinkedListAlgo(Visualization &visualization);

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
    Node::Ptr mDSHead, mDSTail;

private:
    void sceneInit();
};

#endif // ALGORITHMS_SINGLYLINKEDLISTALGO_H

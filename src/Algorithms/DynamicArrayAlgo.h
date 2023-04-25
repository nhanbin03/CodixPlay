#ifndef ALGORITHMS_DYNAMICARRAYALGO_H
#define ALGORITHMS_DYNAMICARRAYALGO_H

#include "../Visualization.h"
#include "Algorithm.h"

#include <functional>
#include <memory>
#include <string>

class DynamicArrayAlgo : public Algorithm {
public:
    static constexpr int MAX_DS_SIZE = 8;

public:
    DynamicArrayAlgo(Visualization& visualization);

    void initializeRandomFixSize(int size);
    void initialize(std::vector<int> list);

    void addElement(int pos, int value);
    void reserveSpaceDouble();

    void deleteElement(int pos);

    void updateValue(int pos, int value);

    void searchValue(int value);

    int getDSSize() const;

private:
    class Block {
    public:
        typedef std::shared_ptr<Block> Ptr;

    public:
        int value;
        int id;

        int referencesId{-1};
        std::map<int, std::string> references;

    public:
        std::string referencesText();
    };

    class Array {
    public:
        int nameId{-1};
        std::vector<Block::Ptr> array;
    };

private:
    Array mDSArray;

    int mDSSize{0};

    std::function<void()> mSceneCleanUp;

private:
    void sceneInit();
    void sceneReset();

    void createArray(Array& arr, std::string name, int length, int yOffset = 0);
    void moveArray(Array& arr, int yOffset);
    void attachReferences(Block::Ptr block);

    void generalCleanUp();

    void relayout();

    void newScene(std::vector<int> lines);
    void addReference(Block::Ptr block, int order, std::string reference);
    void removeReference(Block::Ptr block, std::string reference);
    void clearReference(Block::Ptr block);

    void assignSize(int newSize);

    Vector2 getBlockCenter(Block::Ptr block) const;
};

#endif // ALGORITHMS_DYNAMICARRAYALGO_H

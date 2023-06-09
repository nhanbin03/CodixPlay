#include "DynamicArrayAlgo.h"
#include "../VisualObjects/VisualObject.h"

#include "../Helper.h"

#include <cassert>
#include <iostream>

DynamicArrayAlgo::DynamicArrayAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
    sceneReset();
    createArray(mDSArray, "arr", 1);
    assignSize(0);
}

void DynamicArrayAlgo::initializeRandomFixSize(int size) {
    std::vector<int> list(size);
    for (auto& element : list) {
        element = rand() % 100;
    }
    initialize(list);
}

void DynamicArrayAlgo::initialize(std::vector<int> list) {
    assert(list.size() <= MAX_DS_SIZE);
    sceneReset();

    // New scene
    newScene({});
    int capacity = std::max((int)list.size(), 1);
    createArray(mDSArray, "arr", capacity);
    assignSize(list.size());
    for (int i = 0; i < mDSSize; i++) {
        mDSArray.array[i]->value = list[i];
        mVisualization.setValueBlock(mDSArray.array[i]->id, list[i]);
    }
}

void DynamicArrayAlgo::addElement(int pos, int value) {
    assert(0 <= pos && pos <= mDSSize);
    sceneInit();

    mVisualization.addCode("if (size == capacity)");              // 0
    mVisualization.addCode("    reserveSpace(2 * capacity);");    // 1
    mVisualization.addCode("size++;");                            // 2
    mVisualization.addCode("for (int i = size-1; i > pos; i--)"); // 3
    mVisualization.addCode("    arr[i] = arr[i - 1];");           // 4
    mVisualization.addCode("arr[pos] = value;");                  // 5

    // New scene
    newScene({0});
    int capacity = mDSArray.capacity;

    if (mDSSize == capacity) {
        // New scene
        newScene({1});
        Array tmp;
        createArray(tmp, "tmp", 2 * capacity, -SPACING);
        for (int i = 0; i < mDSSize; i++) {
            mVisualization.setValueBlock(tmp.array[i]->id,
                                         mDSArray.array[i]->value);
            tmp.array[i]->value = mDSArray.array[i]->value;
        }
        std::swap(tmp.array, mDSArray.array);
        std::swap(tmp.capacity, mDSArray.capacity);
        moveArray(tmp, -SPACING);
        moveArray(mDSArray, 0);
        for (int i = 0; i < tmp.capacity; i++) {
            clearReference(tmp.array[i]);
            mVisualization.removeBlock(tmp.array[i]->id);
        }
        mVisualization.removeLabel(tmp.nameId);
    }

    // New scene
    newScene({2});
    mVisualization.setValueBlock(mDSArray.array[mDSSize]->id, 0);
    mDSSize++;

    // New scene
    newScene({3});
    mVisualization.colorBlock(mDSArray.array[mDSSize - 1]->id,
                              VisualColor::getSecondaryColor());

    // Loop
    for (int i = mDSSize - 1; i > pos; i--) {
        // New scene
        newScene({4});
        mVisualization.highlightBlock(mDSArray.array[i - 1]->id);
        mVisualization.setValueBlock(mDSArray.array[i]->id,
                                     mDSArray.array[i - 1]->value);
        mDSArray.array[i]->value = mDSArray.array[i - 1]->value;

        // New scene
        newScene({3});
        mVisualization.unhighlightBlock(mDSArray.array[i]->id);
        mVisualization.colorBlock(mDSArray.array[i - 1]->id,
                                  VisualColor::getSecondaryColor());
    }

    newScene({5});
    mVisualization.colorBlock(mDSArray.array[pos]->id,
                              VisualColor::getTertiaryColor());
    mVisualization.setValueBlock(mDSArray.array[pos]->id, value);
    mDSArray.array[pos]->value = value;
}

void DynamicArrayAlgo::reserveSpace(int newCap) {
    int capacity = mDSArray.capacity;

    sceneInit();

    mVisualization.addCode("if (newCap <= size) return;");     // 0
    mVisualization.addCode("newCap = min(newCap, MAX_SIZE);"); // 1
    mVisualization.addCode("int *tmp = new int[newCap];");     // 2
    mVisualization.addCode("for (int i = 0; i < size; i++)");  // 3
    mVisualization.addCode("    tmp[i] = arr[i];");            // 4
    mVisualization.addCode("capacity = newCap;");              // 5
    mVisualization.addCode("std::swap(tmp, arr);");            // 6
    mVisualization.addCode("delete tmp;");                     // 7

    if (newCap <= mDSSize) {
        // New scene
        newScene({0});
        return;
    }

    // New scene
    newScene({1, 2});
    Array tmp;
    createArray(tmp, "tmp", newCap, -SPACING);

    // New scene
    newScene({3, 4});
    for (int i = 0; i < mDSSize; i++) {
        mVisualization.setValueBlock(tmp.array[i]->id,
                                     mDSArray.array[i]->value);
        tmp.array[i]->value = mDSArray.array[i]->value;
    }

    // New scene
    newScene({5, 6});
    std::swap(tmp.array, mDSArray.array);
    std::swap(tmp.capacity, mDSArray.capacity);
    moveArray(tmp, -SPACING);
    moveArray(mDSArray, 0);

    // New scene
    newScene({7});
    for (int i = 0; i < tmp.capacity; i++) {
        clearReference(tmp.array[i]);
        mVisualization.removeBlock(tmp.array[i]->id);
    }
    mVisualization.removeLabel(tmp.nameId);
}

void DynamicArrayAlgo::deleteElement(int pos) {
    assert(0 <= pos && pos < mDSSize);

    sceneInit();
    mVisualization.addCode("for (int i = pos; i < size-1; i++)"); // 0
    mVisualization.addCode("    arr[i]=arr[i + 1];");             // 1
    mVisualization.addCode("size--;");                            // 2

    // New scene
    newScene({0});
    mVisualization.colorBlock(mDSArray.array[pos]->id,
                              VisualColor::getSecondaryColor());

    // Loop
    for (int i = pos; i < mDSSize - 1; i++) {
        // New scene
        newScene({1});
        mVisualization.highlightBlock(mDSArray.array[i + 1]->id);
        mVisualization.setValueBlock(mDSArray.array[i]->id,
                                     mDSArray.array[i + 1]->value);
        mDSArray.array[i]->value = mDSArray.array[i + 1]->value;

        // New scene
        newScene({0});
        mVisualization.unhighlightBlock(mDSArray.array[i]->id);
        mVisualization.colorBlock(mDSArray.array[i + 1]->id,
                                  VisualColor::getSecondaryColor());
    }

    // New scene
    newScene({2});
    mDSSize--;
    mVisualization.unhighlightBlock(mDSArray.array[mDSSize]->id);
    mVisualization.removeValueBlock(mDSArray.array[mDSSize]->id);
}

void DynamicArrayAlgo::updateValue(int pos, int value) {
    assert(0 <= pos && pos < mDSSize);

    sceneInit();
    mVisualization.addCode("arr[pos] = value;"); // 0

    // New scene
    newScene({0});
    mDSArray.array[pos]->value = value;
    mVisualization.setValueBlock(mDSArray.array[pos]->id, value);
    mVisualization.colorBlock(mDSArray.array[pos]->id,
                              VisualColor::getSecondaryColor());
}

void DynamicArrayAlgo::accessElement(int pos) {
    assert(0 <= pos && pos < mDSSize);

    sceneInit();
    mVisualization.addCode("return arr[pos];"); // 0

    // New scene
    newScene({0});
    mVisualization.colorBlock(mDSArray.array[pos]->id,
                              VisualColor::getSecondaryColor());
}

void DynamicArrayAlgo::searchFirstValue(int value) {
    sceneInit();

    mVisualization.addCode("for (int i = 0; i < size; i++)"); // 0
    mVisualization.addCode("    if (arr[i] == value)");       // 1
    mVisualization.addCode("        return i;");              // 2
    mVisualization.addCode("return NOT_FOUND;");              // 3

    // Loop
    for (int i = 0; i < mDSSize; i++) {
        // New scene
        newScene({0});
        mVisualization.colorBlock(mDSArray.array[i]->id,
                                  VisualColor::getSecondaryColor());

        if (mDSArray.array[i]->value == value) {
            // New scene
            newScene({1, 2});
            mVisualization.colorBlock(mDSArray.array[i]->id,
                                      VisualColor::getTertiaryColor());
            return;
        }

        // New scene
        newScene({1});
        mVisualization.unhighlightBlock(mDSArray.array[i]->id);
    }

    // New scene
    newScene({3});
}

int DynamicArrayAlgo::getDSSize() const {
    return mDSSize;
}

std::string DynamicArrayAlgo::Block::referencesText() {
    std::string returnText = "";
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it != references.begin())
            returnText += "/";
        returnText += it->second;
    }
    return returnText;
}

void DynamicArrayAlgo::sceneInit() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void DynamicArrayAlgo::sceneReset() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    mVisualization.reset();
    mDSArray = Array();
}

void DynamicArrayAlgo::createArray(Array& arr, std::string name, int length,
                                   int yOffset) {
    length = std::min(length, MAX_DS_SIZE);
    if (arr.nameId != -1) {
        mVisualization.removeLabel(arr.nameId);
    }
    arr = Array();
    arr.nameId = mVisualization.createLabel(name + " :");
    mVisualization.setSizeLabel(arr.nameId, 40);
    arr.array = new Block::Ptr[length];
    arr.capacity = length;

    for (int i = 0; i < length; i++) {
        Block::Ptr block = std::make_shared<Block>();
        block->id = mVisualization.createBlock();
        arr.array[i] = block;
        addReference(block, 0, std::to_string(i));
    }
    moveArray(arr, yOffset);
}

void DynamicArrayAlgo::moveArray(Array& arr, int yOffset) {
    mVisualization.moveLabel(
        arr.nameId,
        STARTING_POSITION
            + (Vector2){0, yOffset + VisualObject::ELEMENT_SIZE / 2});
    for (int i = 0; i < arr.capacity; i++) {
        mVisualization.moveBlock(
            arr.array[i]->id,
            STARTING_POSITION
                + (Vector2){SPACING + i * VisualObject::ELEMENT_SIZE, yOffset});
        attachReferences(arr.array[i]);
    }
}

void DynamicArrayAlgo::attachReferences(Block::Ptr block) {
    mVisualization.moveLabel(
        block->referencesId,
        getBlockCenter(block) + (Vector2){0, VisualObject::ELEMENT_SIZE});
}

void DynamicArrayAlgo::generalCleanUp() {
    for (int i = 0; i < mDSArray.capacity; i++) {
        mVisualization.colorBlock(mDSArray.array[i]->id,
                                  VisualColor::getPrimaryColor());
        mVisualization.unhighlightBlock(mDSArray.array[i]->id);
    }
}

void DynamicArrayAlgo::newScene(std::vector<int> lines) {
    mVisualization.createNewScene();
    mVisualization.highlightCode(lines);
}

void DynamicArrayAlgo::addReference(Block::Ptr block, int order,
                                    std::string reference) {
    if (block == nullptr)
        return;
    block->references[order] = reference;
    if (block->referencesId == -1) {
        block->referencesId = mVisualization.createLabel("");
        attachReferences(block);
    }

    mVisualization.updateLabel(block->referencesId, block->referencesText());
}

void DynamicArrayAlgo::removeReference(Block::Ptr block,
                                       std::string reference) {
    assert(block != nullptr);
    for (auto it = block->references.begin(); it != block->references.end();
         it++) {
        if (it->second == reference) {
            block->references.erase(it);
            break;
        }
    }
    mVisualization.updateLabel(block->referencesId, block->referencesText());
}

void DynamicArrayAlgo::clearReference(Block::Ptr block) {
    block->references.clear();
    if (block->referencesId != -1) {
        mVisualization.removeLabel(block->referencesId);
        block->referencesId = -1;
    }
}

void DynamicArrayAlgo::assignSize(int newSize) {
    mDSSize = newSize;
}

Vector2 DynamicArrayAlgo::getBlockCenter(Block::Ptr block) const {
    return mVisualization.getBlockPosition(block->id)
         + (Vector2){VisualObject::ELEMENT_SIZE / 2,
                     VisualObject::ELEMENT_SIZE / 2};
}

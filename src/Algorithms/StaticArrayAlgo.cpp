#include "StaticArrayAlgo.h"
#include "../VisualObjects/VisualObject.h"

#include "../Helper.h"

#include <cassert>
#include <iostream>

StaticArrayAlgo::StaticArrayAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
    sceneInit();
    createArray(mDSArray, "arr", MAX_DS_SIZE);
    assignSize(0);
}

void StaticArrayAlgo::initializeRandomFixSize(int size) {
    std::vector<int> list(size);
    for (auto& element : list) {
        element = rand() % 100;
    }
    initialize(list);
}

void StaticArrayAlgo::initialize(std::vector<int> list) {
    assert(list.size() <= MAX_DS_SIZE);
    sceneReset();

    // New scene
    newScene({});
    int capacity = MAX_DS_SIZE;
    createArray(mDSArray, "arr", capacity);
    assignSize(list.size());
    for (int i = 0; i < mDSSize; i++) {
        mDSArray.array[i]->value = list[i];
        mVisualization.setValueBlock(mDSArray.array[i]->id, list[i]);
    }
}

void StaticArrayAlgo::addElement(int pos, int value) {
    assert(0 <= pos && pos <= mDSSize);
    sceneInit();

    mVisualization.addCode("size++;");                            // 0
    mVisualization.addCode("for (int i = size-1; i > pos; i--)"); // 1
    mVisualization.addCode("    arr[i] = arr[i - 1];");           // 2
    mVisualization.addCode("arr[pos] = value;");                  // 3

    // New scene
    newScene({0});
    mVisualization.setValueBlock(mDSArray.array[mDSSize]->id, 0);
    mDSSize++;

    // New scene
    newScene({1});
    mVisualization.colorBlock(mDSArray.array[mDSSize - 1]->id,
                              VisualColor::getSecondaryColor());

    // Loop
    for (int i = mDSSize - 1; i > pos; i--) {
        // New scene
        newScene({2});
        mVisualization.highlightBlock(mDSArray.array[i - 1]->id);
        mVisualization.setValueBlock(mDSArray.array[i]->id,
                                     mDSArray.array[i - 1]->value);
        mDSArray.array[i]->value = mDSArray.array[i - 1]->value;

        // New scene
        newScene({1});
        mVisualization.unhighlightBlock(mDSArray.array[i]->id);
        mVisualization.colorBlock(mDSArray.array[i - 1]->id,
                                  VisualColor::getSecondaryColor());
    }

    newScene({3});
    mVisualization.colorBlock(mDSArray.array[pos]->id,
                              VisualColor::getTertiaryColor());
    mVisualization.setValueBlock(mDSArray.array[pos]->id, value);
    mDSArray.array[pos]->value = value;
}

void StaticArrayAlgo::deleteElement(int pos) {
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

void StaticArrayAlgo::updateValue(int pos, int value) {
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

void StaticArrayAlgo::accessElement(int pos) {
    assert(0 <= pos && pos < mDSSize);

    sceneInit();
    mVisualization.addCode("return arr[pos];"); // 0

    // New scene
    newScene({0});
    mVisualization.colorBlock(mDSArray.array[pos]->id,
                              VisualColor::getSecondaryColor());
}

void StaticArrayAlgo::searchFirstValue(int value) {
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

int StaticArrayAlgo::getDSSize() const {
    return mDSSize;
}

std::string StaticArrayAlgo::Block::referencesText() {
    std::string returnText = "";
    for (auto it = references.begin(); it != references.end(); it++) {
        if (it != references.begin())
            returnText += "/";
        returnText += it->second;
    }
    return returnText;
}

void StaticArrayAlgo::sceneInit() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    generalCleanUp();
    mVisualization.reset(mVisualization.getLastScene());
}

void StaticArrayAlgo::sceneReset() {
    mSceneCleanUp();
    mSceneCleanUp = []() {};
    mVisualization.reset();
    mDSArray = Array();
}

void StaticArrayAlgo::createArray(Array& arr, std::string name, int length,
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

void StaticArrayAlgo::moveArray(Array& arr, int yOffset) {
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

void StaticArrayAlgo::attachReferences(Block::Ptr block) {
    mVisualization.moveLabel(
        block->referencesId,
        getBlockCenter(block) + (Vector2){0, VisualObject::ELEMENT_SIZE});
}

void StaticArrayAlgo::generalCleanUp() {
    for (int i = 0; i < mDSArray.capacity; i++) {
        mVisualization.colorBlock(mDSArray.array[i]->id,
                                  VisualColor::getPrimaryColor());
        mVisualization.unhighlightBlock(mDSArray.array[i]->id);
    }
}

void StaticArrayAlgo::newScene(std::vector<int> lines) {
    mVisualization.createNewScene();
    mVisualization.highlightCode(lines);
}

void StaticArrayAlgo::addReference(Block::Ptr block, int order,
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

void StaticArrayAlgo::removeReference(Block::Ptr block, std::string reference) {
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

void StaticArrayAlgo::clearReference(Block::Ptr block) {
    block->references.clear();
    if (block->referencesId != -1) {
        mVisualization.removeLabel(block->referencesId);
        block->referencesId = -1;
    }
}

void StaticArrayAlgo::assignSize(int newSize) {
    mDSSize = newSize;
}

Vector2 StaticArrayAlgo::getBlockCenter(Block::Ptr block) const {
    return mVisualization.getBlockPosition(block->id)
         + (Vector2){VisualObject::ELEMENT_SIZE / 2,
                     VisualObject::ELEMENT_SIZE / 2};
}

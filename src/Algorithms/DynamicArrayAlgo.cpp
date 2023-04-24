#include "DynamicArrayAlgo.h"
#include "../VisualObjects/VisualObject.h"

#include "../Helper.h"

#include <cassert>
#include <iostream>

DynamicArrayAlgo::DynamicArrayAlgo(Visualization& visualization)
: Algorithm(visualization) {
    mSceneCleanUp = []() {};
    sceneInit();
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
    int capacity = 1;
    while (capacity < list.size()) {
        capacity *= 2;
    }
    createArray(mDSArray, "arr", capacity);
    assignSize(list.size());
    for (int i = 0; i < mDSSize; i++) {
        mDSArray.array[i]->value = list[i];
        mVisualization.setValueBlock(mDSArray.array[i]->id, list[i]);
    }
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
    if (arr.nameId != -1) {
        mVisualization.removeLabel(arr.nameId);
    }
    arr = Array();
    arr.nameId = mVisualization.createLabel(
        name + " :",
        STARTING_POSITION
            + (Vector2){0, yOffset + VisualObject::ELEMENT_SIZE / 2});
    mVisualization.setSizeLabel(arr.nameId, 40);

    for (int i = 0; i < length; i++) {
        Block::Ptr block = std::make_shared<Block>();
        block->id = mVisualization.createBlock();
        mVisualization.moveBlock(
            block->id,
            STARTING_POSITION
                + (Vector2){
                    SPACING + arr.array.size() * VisualObject::ELEMENT_SIZE,
                    yOffset});
        arr.array.push_back(block);
        addReference(block, 0, std::to_string(i));
    }
}

void DynamicArrayAlgo::generalCleanUp() {
    for (int i = 0; i < mDSArray.array.size(); i++) {
        if (i < mDSSize)
            mVisualization.colorBlock(mDSArray.array[i]->id,
                                      VisualColor::getPrimaryColor());
        else
            mVisualization.colorBlock(mDSArray.array[i]->id,
                                      VisualColor::getSecondaryColor());
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
    if (block->referencesId == -1)
        block->referencesId = mVisualization.createLabel(
            "",
            getBlockCenter(block) + (Vector2){0, VisualObject::ELEMENT_SIZE});

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
    generalCleanUp();
}

Vector2 DynamicArrayAlgo::getBlockCenter(Block::Ptr block) const {
    return mVisualization.getBlockPosition(block->id)
         + (Vector2){VisualObject::ELEMENT_SIZE / 2,
                     VisualObject::ELEMENT_SIZE / 2};
}

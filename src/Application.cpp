#include "Application.h"
#include "ResourceHolders/ResourceIdentifiers.h"
#include "States/CircularLinkedListState.h"
#include "States/DoublyLinkedListState.h"
#include "States/DynamicArrayState.h"
#include "States/HomeState.h"
#include "States/QueueState.h"
#include "States/SinglyLinkedListState.h"
#include "States/StackState.h"
#include "States/StateIdentifiers.h"
#include "States/StaticArrayState.h"

#include "raylib.h"

#include <iostream>

Application::Application()
: mStateStack(State::Context()) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS);

    loadTextures();

    registerStates();
    mStateStack.pushState(StateIDs::SinglyLinkedList);
}

Application::~Application() {
    CloseWindow();
}

void Application::run() {
    while (!WindowShouldClose()) {
        update(GetFrameTime());
        render();
    }
}

void Application::update(float dt) {
    mStateStack.update(dt);
}

void Application::render() {
    BeginDrawing();
    mStateStack.draw();
    EndDrawing();
}

void Application::registerStates() {
    mStateStack.registerState<HomeState>(StateIDs::Home);
    mStateStack.registerState<StaticArrayState>(StateIDs::StaticArray);
    mStateStack.registerState<DynamicArrayState>(StateIDs::DynamicArray);
    mStateStack.registerState<SinglyLinkedListState>(
        StateIDs::SinglyLinkedList);
    mStateStack.registerState<DoublyLinkedListState>(
        StateIDs::DoublyLinkedList);
    mStateStack.registerState<CircularLinkedListState>(
        StateIDs::CircularLinkedList);
    mStateStack.registerState<StackState>(StateIDs::Stack);
    mStateStack.registerState<QueueState>(StateIDs::Queue);
}

void Application::loadTextures() {
    std::string BASE_PATH = "asset/texture/";
    TextureHolder::getInstance().load(TextureID::RewindSceneButton,
                                      BASE_PATH + "RewindSceneButton.png");
    TextureHolder::getInstance().load(TextureID::PrevSceneButton,
                                      BASE_PATH + "PrevSceneButton.png");
    TextureHolder::getInstance().load(TextureID::PlaySceneButton,
                                      BASE_PATH + "PlaySceneButton.png");
    TextureHolder::getInstance().load(TextureID::PauseSceneButton,
                                      BASE_PATH + "PauseSceneButton.png");
    TextureHolder::getInstance().load(TextureID::NextSceneButton,
                                      BASE_PATH + "NextSceneButton.png");
    TextureHolder::getInstance().load(TextureID::FowardSceneButton,
                                      BASE_PATH + "FowardSceneButton.png");
}
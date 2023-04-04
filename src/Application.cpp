#include "Application.h"
#include "States/StateIdentifiers.h"
#include "States/HomeState.h"
#include "States/StaticArrayState.h"
#include "States/DynamicArrayState.h"
#include "States/SinglyLinkedListState.h"
#include "States/DoublyLinkedListState.h"
#include "States/CircularLinkedListState.h"
#include "States/StackState.h"
#include "States/QueueState.h"

#include "raylib.h"

Application::Application()
: mStateStack(State::Context()) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

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
    mStateStack.registerState<SinglyLinkedListState>(StateIDs::SinglyLinkedList);
    mStateStack.registerState<DoublyLinkedListState>(StateIDs::DoublyLinkedList);
    mStateStack.registerState<CircularLinkedListState>(StateIDs::CircularLinkedList);
    mStateStack.registerState<StackState>(StateIDs::Stack);
    mStateStack.registerState<QueueState>(StateIDs::Queue);
}

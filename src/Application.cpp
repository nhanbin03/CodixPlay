#include "Application.h"
#include "ResourceHolders/ResourceIdentifiers.h"
#include "States/CircularLinkedListState.h"
#include "States/DoublyLinkedListState.h"
#include "States/DynamicArrayState.h"
#include "States/HomeState.h"
#include "States/QueueState.h"
#include "States/SettingsState.h"
#include "States/SinglyLinkedListState.h"
#include "States/StackState.h"
#include "States/StateIdentifiers.h"
#include "States/StaticArrayState.h"

#include "raylib.h"

#include <iostream>

Application::Application()
: mStateStack(State::Context()) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS);

    loadTextures();
    loadFonts();

    SetWindowIcon(LoadImageFromTexture(
        TextureHolder::getInstance().get(TextureID::IconLogo)));

    registerStates();
    mStateStack.pushState(StateIDs::Home);
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
    mStateStack.registerState<SettingsState>(StateIDs::Settings);
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
    TextureHolder::getInstance().load(TextureID::Logo, BASE_PATH + "Logo.png");
    TextureHolder::getInstance().load(TextureID::IconLogo,
                                      BASE_PATH + "IconLogo.png");
    TextureHolder::getInstance().load(TextureID::NavHomeButton,
                                      BASE_PATH + "NavHomeButton.png");
    TextureHolder::getInstance().load(TextureID::NavSettingsButton,
                                      BASE_PATH + "NavSettingsButton.png");
    TextureHolder::getInstance().load(TextureID::HeroBanner,
                                      BASE_PATH + "HeroBanner.png");
    TextureHolder::getInstance().load(TextureID::SettingIcon,
                                      BASE_PATH + "SettingIcon.png");
    TextureHolder::getInstance().load(TextureID::StaticArrayCard,
                                      BASE_PATH + "StaticArrayCard.png");
    TextureHolder::getInstance().load(TextureID::DynamicArrayCard,
                                      BASE_PATH + "DynamicArrayCard.png");
    TextureHolder::getInstance().load(TextureID::SinglyLinkedListCard,
                                      BASE_PATH + "SinglyLinkedListCard.png");
    TextureHolder::getInstance().load(TextureID::DoublyLinkedListCard,
                                      BASE_PATH + "DoublyLinkedListCard.png");
    TextureHolder::getInstance().load(TextureID::CircularLinkedListCard,
                                      BASE_PATH + "CircularLinkedListCard.png");
    TextureHolder::getInstance().load(TextureID::StackCard,
                                      BASE_PATH + "StackCard.png");
    TextureHolder::getInstance().load(TextureID::QueueCard,
                                      BASE_PATH + "QueueCard.png");
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
    TextureHolder::getInstance().load(TextureID::SpeedSceneButton,
                                      BASE_PATH + "SpeedSceneButton.png");
    TextureHolder::getInstance().load(TextureID::InitializeTab,
                                      BASE_PATH + "InitializeTab.png");
    TextureHolder::getInstance().load(TextureID::InsertTab,
                                      BASE_PATH + "InsertTab.png");
    TextureHolder::getInstance().load(TextureID::RemoveTab,
                                      BASE_PATH + "RemoveTab.png");
    TextureHolder::getInstance().load(TextureID::SearchTab,
                                      BASE_PATH + "SearchTab.png");
    TextureHolder::getInstance().load(TextureID::UpdateTab,
                                      BASE_PATH + "UpdateTab.png");
}

void Application::loadFonts() {
    std::string BASE_PATH = "asset/font/";
    FontHolder::getInstance().load(FontID::Inter, BASE_PATH + "Inter.ttf");
    FontHolder::getInstance().load(FontID::Inter_Bold,
                                   BASE_PATH + "Inter_Bold.ttf");
    FontHolder::getInstance().load(FontID::Consolas,
                                   BASE_PATH + "Consolas.ttf");
}

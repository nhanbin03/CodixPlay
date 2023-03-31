#include "Application.h"
#include "StateIdentifiers.h"

#include "raylib.h"

Application::Application()
: mStateStack(State::Context()) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

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

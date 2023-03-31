#include "Application.h"

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
        mStateStack.update(GetFrameTime());
        BeginDrawing();
            mStateStack.draw();
        EndDrawing();
    }
}

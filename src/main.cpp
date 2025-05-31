#include <raylib.h>

int maint() {
    SetTraceLogLevel(LOG_WARNING);

    const int screenWidth { 800 };
    const int screenHeight { 450 };
    // Initialize window
    InitWindow(screenWidth, screenHeight, "Cool Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(200, 200, 200, 200, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

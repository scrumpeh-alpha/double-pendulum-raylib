#define RAYGUI_IMPLEMENTATION

#include "UIController.h"
#include "pendulum/double_pendulum.h"
#include "raylib.h"
#include "settings.h"
#include "simulator.h"


// TODO:
// Let the simulator take care of initializing, making pendulum
// Add custom pendulum settings structure (somehow)
// Generalize it enough so that it is (theoretically) possible to add multiple DPs

int main() {
    SetTraceLogLevel(LOG_DEBUG);

    Settings settings {};
    settings.pendulumState = { 30, 50, 0, 0 };
    settings.pendulum1Data = { 150, 10, RED };
    settings.pendulum2Data = { 150, 10, BLUE };

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(settings.screenWidth, settings.screenHeight, "Cool Window");
    SetTargetFPS(settings.FPS);

    float fixedTimeStep { 1.0f / settings.FPS };

    // TODO: Let the simulator take care of this?
    DoublePendulum doublePendulum { settings.pendulumState, settings.pendulum1Data, settings.pendulum2Data, settings.pendulumPivot, settings.gravity };

    TraceLog(LOG_DEBUG, "Gravity %f m/s^2", settings.gravity);
    Simulator sim { doublePendulum, fixedTimeStep };

    UIController uiController { settings };

    float accumulator { 0.0f };

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime() * settings.simSpeed;

        accumulator += deltaTime;

        while (accumulator >= fixedTimeStep) {
            sim.updateElements();
            accumulator -= fixedTimeStep;
        }

        uiController.update();

        BeginDrawing();

        ClearBackground(BLACK);

        sim.drawElements();
        uiController.drawUIElements();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

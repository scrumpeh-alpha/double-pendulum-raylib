#include "pendulum/double_pendulum.h"
#include "pendulum/pendulum_state.h"
#include "simulator.h"
#include <raylib.h>

int main() {
    SetTraceLogLevel(LOG_DEBUG);

    int screenWidth { 1280 };
    int screenHeight { 720 };
    const int targetFPS { 60 };

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Cool Window");
    SetTargetFPS(targetFPS);

    float fixedTimeStep { 1.0f / targetFPS };
    float simSpeed { 5.5f };

    StateVector pendulumState { 30, 50, 0, 0 };
    PendulumData pendulum1 { 150, 10, 20, RED };
    PendulumData pendulum2 { 150, 10, 20, BLUE };
    Vector2 pendulumPivot { screenWidth / 2.0f, screenHeight / 2.0f - 100.0f };

    DoublePendulum doublePendulum { pendulumState, pendulum1, pendulum2, pendulumPivot };

    TraceLog(LOG_DEBUG, "Gravity %f m/s^2", doublePendulum.gravity);
    Simulator sim { doublePendulum, fixedTimeStep };

    float accumulator { 0.0f };

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime() * simSpeed;

        accumulator += deltaTime;

        // TraceLog(LOG_DEBUG, "FrameTime: %f", GetFrameTime());
        while (accumulator >= fixedTimeStep) {
            sim.updateElements();
            accumulator -=  fixedTimeStep;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        sim.drawElements();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#include "pendulum/double_pendulum.h"
#include "pendulum/pendulum_state.h"
#include "simulator.h"
#include <raylib.h>

int main() {
    SetTraceLogLevel(LOG_DEBUG);

    const int screenWidth { 800 };
    const int screenHeight { 450 };

    InitWindow(screenWidth, screenHeight, "Cool Window");
    SetTargetFPS(60);

    StateVector pendulumState { 30, 50, 0, 0 };
    PendulumData pendulum1 { 100, 10, 20, RED };
    PendulumData pendulum2 { 100, 10, 20, BLUE };
    Vector2 pendulumPivot { screenWidth/2.0f, screenHeight/2.0f - 100.0f };

    DoublePendulum doublePendulum { pendulumState, &pendulum1, &pendulum2, pendulumPivot };

    TraceLog(LOG_DEBUG, "Gravity %f m/s^2", doublePendulum.gravity);
    Simulator sim { doublePendulum, 0.1 };

    while (!WindowShouldClose()) {

        sim.updateElements();

        BeginDrawing();

        ClearBackground(BLACK);

        sim.drawElements();
        // DrawRectangle(200, 200, 200, 200, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

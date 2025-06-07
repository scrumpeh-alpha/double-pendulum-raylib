#pragma once
#include "pendulum/pendulum_state.h"

struct Settings {
    int screenWidth { 1280 };
    int screenHeight { 720 };
    inline static constexpr int FPS { 60 };

    StateVector pendulumState {};
    PendulumData pendulum1Data {};
    PendulumData pendulum2Data {};
    Vector2 pendulumPivot { screenWidth / 3.0f, screenHeight / 2.0f - 100.0f };

    // TODO: Should be part of simulator?
    float simSpeed { 10.0f };
    // gravity , where to put that?
};

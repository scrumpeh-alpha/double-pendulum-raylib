#pragma once
#include "raylib.h"

struct StateVector {
    float theta1, theta2, omega1, omega2;
};

struct PendulumData {
    float length;
    float mass;
    float radius;
    Color color;
    Vector2 pos;
};

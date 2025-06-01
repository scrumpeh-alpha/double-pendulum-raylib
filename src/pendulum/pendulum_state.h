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
};


StateVector operator+(StateVector lhs, const StateVector& rhs); 
StateVector operator+(StateVector lhs, float rhs);
StateVector& operator+=(StateVector& lhs, float rhs);
StateVector operator*(StateVector lhs, float rhs);
StateVector operator*(float lhs, StateVector rhs);
StateVector operator/(StateVector lhs, float rhs);
StateVector operator/(float lhs, StateVector rhs);

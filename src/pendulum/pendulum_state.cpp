#include "pendulum_state.h"

StateVector operator+(StateVector lhs, const StateVector& rhs) {
    lhs.theta1 += rhs.theta1;
    lhs.theta2 += rhs.theta2;
    lhs.omega1 += rhs.omega1;
    lhs.omega2 += rhs.omega2;
    return lhs;
}

StateVector operator+(StateVector lhs, float rhs) {
    lhs.theta1 += rhs;
    lhs.theta2 += rhs;
    lhs.omega1 += rhs;
    lhs.omega2 += rhs;
    return lhs;
}

StateVector& operator+=(StateVector& lhs, float rhs) {
    lhs.theta1 += rhs;
    lhs.theta2 += rhs;
    lhs.omega1 += rhs;
    lhs.omega2 += rhs;
    return lhs;
}

StateVector operator*(StateVector lhs, float rhs) {
    lhs.theta1 *= rhs;
    lhs.theta2 *= rhs;
    lhs.omega1 *= rhs;
    lhs.omega2 *= rhs;
    return lhs;
}

StateVector operator*(float lhs, StateVector rhs) {
    return rhs * lhs;
}

StateVector operator/(StateVector lhs, float rhs) {
    lhs.theta1 /= rhs;
    lhs.theta2 /= rhs;
    lhs.omega1 /= rhs;
    lhs.omega2 /= rhs;
    return lhs;
}

StateVector operator/(float lhs, StateVector rhs) {
    return rhs / lhs;
}

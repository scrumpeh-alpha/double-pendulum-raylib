#include "double_pendulum.h"
#include "pendulum_state.h"
#include "raylib.h"
#include <cmath>
#include "../util/math-util.h"

StateVector DoublePendulum::phi(const StateVector& state) {
    using Math::square;

    float m1 = m_p1->mass;
    float m2 = m_p2->mass;
    float l1 = m_p1->length;
    float l2 = m_p2->length;
    float g = gravity;
    float dtheta = state.theta1 - state.theta2;

    StateVector stateCopy { state };
    stateCopy.theta1 = state.omega1;
    stateCopy.theta2 = state.omega2;

    stateCopy.omega1 = (-m2 * (l1 * square(state.omega1) * sin(dtheta) * cos(dtheta) + l2 * square(state.omega2) * sin(dtheta)) + g * (-(m1 + m2) * sin(state.theta1) + m2 * cos(dtheta) * sin(state.theta2))) / (m1 * l1 + m2 * l1 * square(sin(dtheta)));

    stateCopy.omega2 =
        ((m1 + m2) * l1 * square(state.omega1) * sin(dtheta) + m2 * l2 * square(state.omega2) * sin(dtheta) * cos(dtheta) + (m1 + m2) * g * (sin(state.theta1) * cos(dtheta) - sin(state.theta2))) / (m1 * l2 + m2 * l2 * square(sin(dtheta)));

    return stateCopy;
}

StateVector DoublePendulum::rk4Step(const StateVector& state, float dt) {
    StateVector k1 = phi(state);
    StateVector k2 = phi(state + dt * k1 / 2);
    StateVector k3 = phi(state + dt * k2 / 2);
    StateVector k4 = phi(state + dt * k3);
    return state + dt / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
}

void DoublePendulum::update(float dt) {
    if (std::isnan(m_stateVector.theta1))
        m_stateVector.theta1 = 0;
    if (std::isnan(m_stateVector.theta2))
        m_stateVector.theta2 = 0;
    // TraceLog(LOG_WARNING, std::to_string(m_stateVector.omega2).data());
    m_stateVector = rk4Step(m_stateVector, dt);

    m_pos1.x = m_pivot.x + m_p1->length * sin(m_stateVector.theta1);
    m_pos1.y = m_pivot.y + m_p1->length * cos(m_stateVector.theta1);
    m_pos2.x = m_pos1.x + m_p2->length * sin(m_stateVector.theta2);
    m_pos2.y = m_pos1.y + m_p2->length * cos(m_stateVector.theta2);
}

void DoublePendulum::draw() {
    DrawLine(m_pivot.x, m_pivot.y, m_pos1.x, m_pos1.y, GRAY);
    DrawLine(m_pos1.x, m_pos1.y, m_pos2.x, m_pos2.y, GRAY);
    DrawCircle(m_pos1.x, m_pos1.y, m_p1->radius, m_p1->color);
    DrawCircle(m_pos2.x, m_pos2.y, m_p2->radius, m_p2->color);
}

#include "double_pendulum.h"
#include "../util/math-util.h"
#include "pendulum_state.h"
#include "raylib.h"
#include <cmath>

StateVector DoublePendulum::phi(const StateVector& state) const {
    using Math::square;

    float m1 = m_p1.mass;
    float m2 = m_p2.mass;
    float l1 = m_p1.length;
    float l2 = m_p2.length;
    float g = gravity;
    float dtheta = state.theta1 - state.theta2;

    StateVector newState { };
    newState.theta1 = state.omega1;
    newState.theta2 = state.omega2;

    newState.omega1 = (-m2 * (l1 * square(state.omega1) * sin(dtheta) * cos(dtheta) + l2 * square(state.omega2) * sin(dtheta)) + g * (-(m1 + m2) * sin(state.theta1) + m2 * cos(dtheta) * sin(state.theta2))) / (m1 * l1 + m2 * l1 * square(sin(dtheta)));

    newState.omega2 =
        ((m1 + m2) * l1 * square(state.omega1) * sin(dtheta) + m2 * l2 * square(state.omega2) * sin(dtheta) * cos(dtheta) + (m1 + m2) * g * (sin(state.theta1) * cos(dtheta) - sin(state.theta2))) / (m1 * l2 + m2 * l2 * square(sin(dtheta)));

    return newState;
}

StateVector DoublePendulum::rk4Step(const StateVector& state, float dt) const {
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

    m_pos.first.x = m_pivot.x + m_p1.length * sin(m_stateVector.theta1);
    m_pos.first.y = m_pivot.y + m_p1.length * cos(m_stateVector.theta1);
    m_pos.second.x = m_pos.first.x + m_p2.length * sin(m_stateVector.theta2);
    m_pos.second.y = m_pos.first.y + m_p2.length * cos(m_stateVector.theta2);
}



void DoublePendulum::draw() const {
    DrawLine(m_pivot.x, m_pivot.y, m_pos.first.x, m_pos.first.y, GRAY);
    DrawLine(m_pos.first.x, m_pos.first.y, m_pos.second.x, m_pos.second.y, GRAY);
    DrawCircle(m_pos.first.x, m_pos.first.y, radius1(), m_p1.color);
    DrawCircle(m_pos.second.x, m_pos.second.y, radius2(), m_p2.color);
}

void DoublePendulum::handleMouse(Vector2 mousePos, Vector2 mouseVel) {
    bool movePendulum1 = CheckCollisionPointCircle(mousePos, m_pos.first, radius1()) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    bool movePendulum2 = CheckCollisionPointCircle(mousePos, m_pos.second, radius2()) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    if (movePendulum1 && !m_isHeld.second || m_isHeld.first) {
        Vector2 relMousePos { mousePos.x - m_pivot.x, -mousePos.y + m_pivot.y };
        // TraceLog(LOG_DEBUG, "Relative Mouse Pos: (%f, %f)", relMousePos.x, relMousePos.y);
        if (relMousePos.x == 0)
            relMousePos.x = 1e-9;
        float mouseTheta { std::atan(relMousePos.y / relMousePos.x) + PI / 2.0f };
        if (relMousePos.x < 0)
            mouseTheta += PI;
        // TraceLog(LOG_DEBUG, "Mouse Theta: %f rad", mouseTheta);
        m_stateVector.theta1 = mouseTheta;
        m_stateVector.omega1 = 0;
        m_stateVector.omega2 = 0;
        m_isHeld.first = true;
    }
    if (movePendulum2 && !m_isHeld.first || m_isHeld.second) {
        Vector2 relMousePos { mousePos.x - m_pos.first.x, -mousePos.y + m_pos.first.y };
        if (relMousePos.x == 0)
            relMousePos.x = 1e-9;
        float mouseTheta { std::atan(relMousePos.y / relMousePos.x) + PI / 2.0f };
        if (relMousePos.x < 0)
            mouseTheta += PI;
        m_stateVector.theta2 = mouseTheta;
        m_stateVector.omega1 = 0;
        m_stateVector.omega2 = 0;
        m_isHeld.second = true;
    }

    if (IsMouseButtonUp(MOUSE_LEFT_BUTTON)) {
        m_isHeld.first = false;
        m_isHeld.second = false;
    }
}

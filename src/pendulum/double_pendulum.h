#pragma once
#include "pendulum_state.h"
#include "raylib.h"
#include <algorithm>
#include <utility>

class DoublePendulum {
  private:
    StateVector& m_stateVector;
    float& m_gravity;
    PendulumData& m_p1;
    PendulumData& m_p2;
    Vector2& m_pivot;

    std::pair<Vector2, Vector2> m_pos {};
    std::pair<bool, bool> m_isHeld {};
    // Vector2 m_pos1 {};
    // Vector2 m_pos2 {};
    // bool p1IsHeld { false };
    // bool p2IsHeld { false };

  public:
    DoublePendulum(StateVector& initialStateVector, PendulumData& p1, PendulumData& p2, Vector2& pivot, float& gravity)
        : m_stateVector { initialStateVector }, m_p1 { p1 }, m_p2 { p2 }, m_pivot { pivot }, m_gravity { gravity } {};

    void update(float dt);
    void draw() const;
    void handleMouse(Vector2 mousePos, Vector2 mouseVel);

    float radius1() const {
        return std::max(10.0f, 1.5f * m_p1.mass);
    }

    float radius2() const {
        return std::max(10.0f, 1.5f * m_p2.mass);
    }

  private:
    StateVector phi(const StateVector& state) const;
    StateVector rk4Step(const StateVector& state, float dt) const;
};

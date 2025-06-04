#pragma once
#include "pendulum_state.h"
#include "raylib.h"
#include <utility>

class DoublePendulum {
  public:
    float gravity { 9.8 };

  private:
    StateVector& m_stateVector;
    PendulumData& m_p1;
    PendulumData& m_p2;
    Vector2 m_pivot {};

    std::pair<Vector2, Vector2> m_pos {};
    std::pair<bool, bool> m_isHeld{};
    // Vector2 m_pos1 {};
    // Vector2 m_pos2 {};
    // bool p1IsHeld { false };
    // bool p2IsHeld { false };

  public:
    DoublePendulum(StateVector& initialStateVector, PendulumData& p1, PendulumData& p2, Vector2 pivot)
        : m_stateVector { initialStateVector }, m_p1 { p1 }, m_p2 { p2 }, m_pivot { pivot } {};

    void update(float dt);
    void draw() const;
    void handleMouse(Vector2 mousePos, Vector2 mouseVel);

  private:
    StateVector phi(const StateVector& state) const;
    StateVector rk4Step(const StateVector& state, float dt) const;
};

#pragma once
#include "pendulum_state.h"
#include "raylib.h"

class DoublePendulum {
  private:
    StateVector* m_stateVector;
    PendulumData* m_p1;
    PendulumData* m_p2;
    Vector2 m_pivot;

  public:
    DoublePendulum(StateVector* initialStateVector, PendulumData* p1, PendulumData* p2, Vector2 pivot)
        : m_stateVector { initialStateVector }, m_p1 { p1 }, m_p2 { p2 }, m_pivot { pivot } {};

    void update(float dt);
    void draw();

  private:
    StateVector* phi(StateVector* state);
    void rk4Step(float dt);
};

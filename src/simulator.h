#pragma once
#include "pendulum/double_pendulum.h"

class Simulator {
  private:
    DoublePendulum& m_dp;
    float m_timeStep {};
    float m_gravity {};

  public:
    Simulator(DoublePendulum& dp, float timeStep = 0.1, float gravity = 9.8);
    // ~Simulator();

    void updateElements() const;
    void drawElements() const;

    float getTimeStep() const;
    void setTimeStep(float timeStep);
};

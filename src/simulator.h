#pragma once
#include "pendulum/double_pendulum.h"

class Simulator {
  public:
    float gravity { 9.8f };

  private:
    DoublePendulum& m_dp;
    float m_timeStep {};

  public:
    Simulator(DoublePendulum& dp, float timeStep = 0.1);
    // ~Simulator();

    void updateElements() const;
    void drawElements() const;

    float getTimeStep() const;
    void setTimeStep(float timeStep);
};

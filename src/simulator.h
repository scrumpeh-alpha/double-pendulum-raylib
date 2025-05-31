#pragma once
#include "pendulum/double_pendulum.h"

class Simulator {
private:
    float timeStep;
    float gravity;
    DoublePendulum dp;
public:
    Simulator();
    ~Simulator();

    void drawElements();

    void advanceTimeStep();
    float getTimeStep();
    void setTimeStep(float timeStep);
};

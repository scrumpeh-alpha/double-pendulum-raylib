#include "simulator.h"
#include "pendulum/double_pendulum.h"

Simulator::Simulator(DoublePendulum& dp, float timeStep, float gravity)
    : m_timeStep { timeStep }, m_gravity { gravity }, m_dp { dp } {
}

void Simulator::updateElements() {
    m_dp.update(m_timeStep);
}

void Simulator::drawElements() {
    m_dp.draw();
}

float Simulator::getTimeStep() { return m_timeStep; }

void Simulator::setTimeStep(float timeStep) { m_timeStep = timeStep; }

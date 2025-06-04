#include "simulator.h"
#include "pendulum/double_pendulum.h"
#include "raylib.h"

Simulator::Simulator(DoublePendulum& dp, float timeStep, float gravity)
    : m_timeStep { timeStep }, m_gravity { gravity }, m_dp { dp } {
}

void Simulator::updateElements() const {
    Vector2 mousePos = GetMousePosition();
    Vector2 mouseVel = GetMouseDelta();

    m_dp.handleMouse(mousePos, mouseVel);
    m_dp.update(m_timeStep);
}

void Simulator::drawElements() const {
    m_dp.draw();
}

float Simulator::getTimeStep() const { return m_timeStep; }

void Simulator::setTimeStep(float timeStep) { m_timeStep = timeStep; }

#include "pendulum/pendulum_state.h"
#include "raygui.h"

class UIController {
  private:
    Vector2 m_anchor;
    StateVector& m_pendulumState;
    PendulumData& m_pendulum1;
    PendulumData& m_pendulum2;

    int m_screenWidth, m_screenHeight;
    Rectangle m_margin { 0, 20.0f, 20.0f, 20.0f };
    Rectangle m_mainBounds {};

  public:
    UIController(Vector2 anchor, StateVector& pendulumState, PendulumData& pendulum1, PendulumData& pendulum2);

    void drawUIElements();
};

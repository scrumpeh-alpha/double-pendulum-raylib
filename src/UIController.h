#include "raygui.h"
#include "settings.h"

class UIController {
  private:
    // StateVector& m_pendulumState;
    // PendulumData& m_pendulum1;
    // PendulumData& m_pendulum2;
    //
    // int m_screenWidth, m_screenHeight;
    Vector2 m_anchor;
    Settings& m_settings;
    Rectangle m_margin { 0, 20.0f, 20.0f, 20.0f };
    Rectangle m_mainBounds;

  public:
    UIController(Settings& settings);

    void update();
    void drawUIElements();
};

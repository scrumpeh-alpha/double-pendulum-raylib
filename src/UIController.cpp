#include "UIController.h"
#include "raygui.h"
#include "raylib.h"
#include <iomanip>
#include <sstream>

// TODO:
// Generalize this
UIController::UIController(Vector2 anchor, StateVector& pendulumState, PendulumData& pendulum1, PendulumData& pendulum2)
    : m_anchor { anchor }, m_pendulumState { pendulumState },  //
      m_pendulum1 { pendulum1 }, m_pendulum2 { pendulum2 },    //
      m_screenWidth { GetScreenWidth() }, m_screenHeight { GetScreenHeight() } {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
}

// UNSAFE?
// char* floatToChar(float value, int decimalPlaces) {
//     const int bufferSize { 32 };
//     char* buffer = new char[bufferSize];
//     snprintf(buffer, bufferSize, "%.*f", decimalPlaces, value);
//     return buffer;
// }

std::string floatToString(float value, int decimalPlaces) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(decimalPlaces) << value;
    return ss.str();
}

void UIController::drawUIElements() {
    // Update screen height and width in case of resize
    m_screenWidth = GetScreenWidth();
    m_screenHeight = GetScreenHeight();
    m_mainBounds = { m_anchor.x + m_margin.x,
                     m_anchor.y + m_margin.y,
                     m_screenWidth - m_anchor.x - m_margin.width,
                     (float)m_screenHeight - 2 * m_margin.height };

    GuiGroupBox(m_mainBounds, "Double Pendulum Parameters");

    Vector2 internalPadding { 15.0f, 15.0f };
    Rectangle p1ControlBounds { m_mainBounds.x + internalPadding.x, m_mainBounds.y, m_mainBounds.width - internalPadding.x, m_mainBounds.height / 3 - 50 };
    GuiLabel({ p1ControlBounds.x, p1ControlBounds.y, p1ControlBounds.width, 100.0f }, "Pendulum 1");

    float verticalGap { 50.0f };

    std::string valueString { floatToString(m_pendulum1.length, 2) };
    GuiSliderBar({ p1ControlBounds.x + 100, p1ControlBounds.y + verticalGap + 25, p1ControlBounds.width - 200, 25 }, "Length: ", valueString.c_str(), &m_pendulum1.length, 50, 500);

    valueString = floatToString(m_pendulum1.mass, 2);
    GuiSliderBar({ p1ControlBounds.x + 100, p1ControlBounds.y + 2 * verticalGap + 25, p1ControlBounds.width - 200, 25 }, "Mass: ", valueString.c_str(), &m_pendulum1.mass, 1, 50);

    Rectangle p2ControlBounds { p1ControlBounds.x, p1ControlBounds.height + 50, p1ControlBounds.width, p1ControlBounds.height };

    GuiLabel({ p2ControlBounds.x, p2ControlBounds.y, p2ControlBounds.width, 100.0f }, "Pendulum 2");

    valueString = floatToString(m_pendulum2.length, 2);
    GuiSliderBar({ p2ControlBounds.x + 100, p2ControlBounds.y + verticalGap + 25, p2ControlBounds.width - 200, 25 }, "Length: ", valueString.c_str(), &m_pendulum2.length, 50, 500);

    valueString = floatToString(m_pendulum2.mass, 2);
    GuiSliderBar({ p2ControlBounds.x + 100, p2ControlBounds.y + 2 * verticalGap + 25, p2ControlBounds.width - 200, 25 }, "Mass: ", valueString.c_str(), &m_pendulum2.mass, 1, 50);
}

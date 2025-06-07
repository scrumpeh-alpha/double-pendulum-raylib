#include "UIController.h"
#include "raygui.h"
#include "raylib.h"
#include <iomanip>
#include <sstream>

UIController::UIController(Settings& settings)
    : m_settings { settings },  //
      m_anchor { settings.screenWidth * 2 / 3.0f, 0 } {
    GuiLoadStyle("../styles/circuit.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    m_mainBounds = { m_anchor.x + m_margin.x,
                     m_anchor.y + m_margin.y,
                     m_settings.screenWidth - m_anchor.x - m_margin.width,
                     (float)m_settings.screenHeight - 2 * m_margin.height };
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

void UIController::update() {
    m_settings.screenWidth = GetScreenWidth();
    m_settings.screenHeight = GetScreenHeight();
    m_settings.pendulumPivot = { m_settings.screenWidth / 3.0f, m_settings.screenHeight / 2.0f - 100.0f };
    m_anchor.x = 2 * m_settings.screenWidth / 3.0f;

    m_mainBounds = { m_anchor.x + m_margin.x,
                     m_anchor.y + m_margin.y,
                     m_settings.screenWidth - m_anchor.x - m_margin.width,
                     (float)m_settings.screenHeight - 2 * m_margin.height };
}

void UIController::drawUIElements() {
    GuiGroupBox(m_mainBounds, "Double Pendulum Parameters");

    Vector2 internalPadding { 15.0f, 15.0f };
    Rectangle p1ControlBounds { m_mainBounds.x + internalPadding.x, m_mainBounds.y, m_mainBounds.width - internalPadding.x, m_mainBounds.height / 3 - 50 };
    GuiLabel({ p1ControlBounds.x, p1ControlBounds.y, p1ControlBounds.width, 100.0f }, "Pendulum 1");

    float verticalGap { 50.0f };

    std::string valueString { floatToString(m_settings.pendulum1Data.length, 2) };
    GuiSliderBar({ p1ControlBounds.x + 100, p1ControlBounds.y + verticalGap + 25, p1ControlBounds.width - 200, 25 }, "Length: ", valueString.c_str(), &m_settings.pendulum1Data.length, 50, 500);

    valueString = floatToString(m_settings.pendulum1Data.mass, 2);
    GuiSliderBar({ p1ControlBounds.x + 100, p1ControlBounds.y + 2 * verticalGap + 25, p1ControlBounds.width - 200, 25 }, "Mass: ", valueString.c_str(), &m_settings.pendulum1Data.mass, 1, 50);

    Rectangle p2ControlBounds { p1ControlBounds.x, p1ControlBounds.height + 50, p1ControlBounds.width, p1ControlBounds.height };

    GuiLabel({ p2ControlBounds.x, p2ControlBounds.y, p2ControlBounds.width, 100.0f }, "Pendulum 2");

    valueString = floatToString(m_settings.pendulum2Data.length, 2);
    GuiSliderBar({ p2ControlBounds.x + 100, p2ControlBounds.y + verticalGap + 25, p2ControlBounds.width - 200, 25 }, "Length: ", valueString.c_str(), &m_settings.pendulum2Data.length, 50, 500);

    valueString = floatToString(m_settings.pendulum2Data.mass, 2);
    GuiSliderBar({ p2ControlBounds.x + 100, p2ControlBounds.y + 2 * verticalGap + 25, p2ControlBounds.width - 200, 25 }, "Mass: ", valueString.c_str(), &m_settings.pendulum2Data.mass, 1, 50);

    // For simulation parameters
    // Rectangle simControlBounds { p2ControlBounds.x, p2ControlBounds.height + verticalGap, p2ControlBounds.width, p2ControlBounds.height };

}

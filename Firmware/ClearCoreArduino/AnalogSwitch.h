// AnalogSwitch.h
#ifndef ANALOG_SWITCH_H
#define ANALOG_SWITCH_H

#include "ClearCore.h"

class AnalogSwitch {
public:
    // Constructor that takes a reference to an analog input
    AnalogSwitch(DigitalInAnalogIn& analogInput) : m_analogInput(analogInput) {}

    void Init() {
        m_analogInput.Mode(Connector::INPUT_ANALOG);
    }

    // Method to get the current switch position
    int GetSwitchPosition() {
        float voltage = m_analogInput.AnalogVoltage();
        if (voltage < 1.65) {
            return 0;
        } else if (voltage < 4.95) {
            return 1;
        } else if (voltage < 8.25) {
            return 2;
        } else {
            return 3;
        }
    }

private:
    DigitalInAnalogIn& m_analogInput;
};

#endif // ANALOG_SWITCH_H

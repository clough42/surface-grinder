// MachineAxis.h
#ifndef MACHINE_AXIS_H
#define MACHINE_AXIS_H

#include <cstdint>
#include "ClearCore.h" // Include the ClearCore library

#define STEPS_PER_REV 1000
#define SECONDS_PER_MINUTE 60
#define RPM * STEPS_PER_REV / SECONDS_PER_MINUTE
#define MAX_VELOCITY 10 RPM
#define MAX_ACCELERATION 500

class MachineAxis {
public:
    MachineAxis(MotorDriver& motor, int32_t numerator, int32_t denominator, ClearCorePins eStopPin)
        : m_stepsPerNmNumerator(numerator), m_stepsPerNmDenominator(denominator), m_motor(motor), m_eStopPin(eStopPin) {}

    void Init();

    void Move(int32_t positionInNanometers);

    int32_t GetPositionInNanometers() const;

    bool IsMoveComplete() const;

    void ClearAlerts();

private:
    // Ratio of nanometers to motor steps
    int32_t m_stepsPerNmNumerator;
    int32_t m_stepsPerNmDenominator;

    // The motor driver to use for this axis
    MotorDriver &m_motor;

    // EStop pin
    ClearCorePins m_eStopPin;
};

#endif // MACHINE_AXIS_H

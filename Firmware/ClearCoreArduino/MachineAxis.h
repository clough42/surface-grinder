// MachineAxis.h
#ifndef MACHINE_AXIS_H
#define MACHINE_AXIS_H

#include <cstdint>
#include "ClearCore.h" // Include the ClearCore library
#include "CommonEnums.h"

#define STEPS_PER_REV 1000
#define SECONDS_PER_MINUTE 60
#define RPM * STEPS_PER_REV / SECONDS_PER_MINUTE
#define MAX_VELOCITY 1000 RPM
#define MAX_ACCELERATION 50000

class MachineAxis {
public:

    MachineAxis(MotorDriver& motor, int32_t stepsPerNmNumerator, int32_t stepsPerNmDenominator, ClearCorePins eStopPin, Direction motorDirection = Direction::NORMAL)
        : m_stepsPerNmNumerator(stepsPerNmNumerator), m_stepsPerNmDenominator(stepsPerNmDenominator), m_motor(motor), m_eStopPin(eStopPin), m_motorDirection(motorDirection) {}

    void Init();
    void MoveToPositionNm(int32_t positionInNanometers);
	void JogNm(int32_t distanceInNanometers);
    int32_t GetCurrentPositionNm() const;
    int32_t GetLastCommandedPositionNm() const;
    bool IsMoveComplete() const;
    void ResetAndEnable();

private:
    // Ratio of nanometers to motor steps
    int32_t m_stepsPerNmNumerator;
    int32_t m_stepsPerNmDenominator;

    // The motor driver to use for this axis
    MotorDriver &m_motor;

    // Direction config
    Direction m_motorDirection;

    // EStop pin
    ClearCorePins m_eStopPin;

    // Last commanded position in nanometers
    int32_t m_lastCommandedPosition;
};

#endif // MACHINE_AXIS_H

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

    void initHardware() {
        m_motor.EStopConnector(m_eStopPin);
        m_motor.EnableRequest(true);
		m_motor.VelMax(MAX_VELOCITY);
        m_motor.AccelMax(MAX_ACCELERATION);
        m_motor.MoveStopDecel(0);
    }

    void Move(int32_t positionInNanometers) {
        m_targetMotorSteps = (positionInNanometers * m_stepsPerNmNumerator) / m_stepsPerNmDenominator;
        m_motor.Move(m_targetMotorSteps, StepGenerator::MOVE_TARGET_ABSOLUTE);
    }

    int32_t GetPositionInNanometers() const {
        int32_t motorSteps = m_motor.PositionRefCommanded();
        return (motorSteps * m_stepsPerNmDenominator) / m_stepsPerNmNumerator;
    }

    bool IsMoveComplete() const {
        return m_motor.StepsComplete() && m_motor.PositionRefCommanded() == m_targetMotorSteps;
    }

    void ClearAlerts() {
        m_motor.ClearAlerts();
    }

private:
    // Ratio of nanometers to motor steps
    int32_t m_stepsPerNmNumerator;
    int32_t m_stepsPerNmDenominator;

    int32_t m_targetMotorSteps = 0;

    // The motor driver to use for this axis
    MotorDriver &m_motor;

    // EStop pin
    ClearCorePins m_eStopPin;
};

#endif // MACHINE_AXIS_H

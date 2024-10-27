#include "MachineAxis.h"
#include "HMIConstants.h"

void MachineAxis::Init() {
    m_motor.EStopConnector(m_eStopPin);
    m_motor.EnableRequest(true);
    m_motor.VelMax(MAX_VELOCITY);
    m_motor.AccelMax(MAX_ACCELERATION);
    m_motor.MoveStopDecel(0);
}

void MachineAxis::Move(int32_t positionInNanometers) {
    int32_t motorSteps = (positionInNanometers * m_stepsPerNmNumerator) / m_stepsPerNmDenominator;
    m_motor.Move(motorSteps, StepGenerator::MOVE_TARGET_ABSOLUTE);
}

int32_t MachineAxis::GetPositionInNanometers() const {
    int32_t motorSteps = m_motor.PositionRefCommanded();
    return (motorSteps * m_stepsPerNmDenominator) / m_stepsPerNmNumerator;
}

bool MachineAxis::IsMoveComplete() const {
    return m_motor.StepsComplete();
}

void MachineAxis::ClearAlerts() {
    m_motor.ClearAlerts();
}
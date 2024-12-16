// Copyright (c) 2004 James Clough (Clough42, LLC)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "MachineAxis.h"
#include <Arduino.h>

void MachineAxis::Init() {
	// initialize motor
	m_motor.HlfbMode(ClearCore::MotorDriver::HlfbModes::HLFB_MODE_HAS_BIPOLAR_PWM);
	m_motor.HlfbCarrier(MotorDriver::HLFB_CARRIER_482_HZ); 
	m_motor.EStopConnector(m_eStopPin);
	m_motor.VelMax(MAX_VELOCITY);
	m_motor.AccelMax(MAX_ACCELERATION);
	m_motor.MoveStopAbrupt();

	// Enable the motor and jog back and forth one step to cancel auto-home
	m_motor.ClearAlerts();
    m_motor.EnableRequest(true);
	delay(20);
	m_motor.Move(1, StepGenerator::MOVE_TARGET_REL_END_POSN);
	delay(20);
	m_motor.Move(-1, StepGenerator::MOVE_TARGET_REL_END_POSN);
	delay(20);
	m_motor.PositionRefSet(CalculateMotorSteps(m_lastCommandedPosition));

	Serial.println("Finish MachineAxis::Init");
}

void MachineAxis::MoveToPositionNm(int32_t positionInNanometers) {
	Serial.println("MachineAxis::MoveToPosition");
	Serial.println(positionInNanometers);
    m_motor.Move(CalculateMotorSteps(positionInNanometers), StepGenerator::MOVE_TARGET_ABSOLUTE);
    m_lastCommandedPosition = positionInNanometers;
}

int32_t MachineAxis::CalculateMotorSteps(int64_t positionInNanometers) const {
	int64_t motorSteps = (static_cast<int64_t>(positionInNanometers) * m_stepsPerNmNumerator) / m_stepsPerNmDenominator;
	return static_cast<int32_t>(motorSteps) * static_cast<int>(m_motorDirection);
}

void MachineAxis::JogNm(int32_t distanceInNanometers)
{
	Serial.println("MachineAxis::JogNm");
	if (!IsDisabled()) {
		MoveToPositionNm(m_lastCommandedPosition + distanceInNanometers);
	}
}

int32_t MachineAxis::GetCurrentPositionNm() const {
    int32_t motorSteps = m_motor.PositionRefCommanded() * static_cast<int>(m_motorDirection);
    int64_t currentPositionNm = (static_cast<int64_t>(motorSteps) * m_stepsPerNmDenominator) / m_stepsPerNmNumerator;
	return static_cast<int32_t>(currentPositionNm);
}

int32_t MachineAxis::GetLastCommandedPositionNm() const
{
	return m_lastCommandedPosition;
}

bool MachineAxis::IsReady() const {
    //ClearCore::MotorDriver::MotorReadyStates readyState = m_motor.StatusReg().bit.ReadyState;
	//PrintReadyState(readyState);
	//return readyState == ClearCore::MotorDriver::MotorReadyStates::MOTOR_READY;
	return m_motor.HlfbState() == MotorDriver::HLFB_ASSERTED;
}

bool MachineAxis::IsDisabled() const {
    ClearCore::MotorDriver::MotorReadyStates readyState = m_motor.StatusReg().bit.ReadyState;
	PrintReadyState(readyState);
    return readyState == ClearCore::MotorDriver::MotorReadyStates::MOTOR_DISABLED;
}

void MachineAxis::StartHomingCycle() {
	m_motor.EnableRequest(false);
	delay(20);
	m_motor.EnableRequest(true);
	delay(20);
	m_motor.MoveVelocity(1000 * static_cast<int>(m_motorDirection) * static_cast<int>(m_homingDirection));
	delay(20);
}

bool MachineAxis::IsHomingCycleComplete() {
	if (m_motor.HlfbState() == MotorDriver::HLFB_ASSERTED) {
		m_motor.MoveStopAbrupt();
		delay(20);
		m_motor.Move(-1 * static_cast<int>(m_motorDirection) * static_cast<int>(m_homingDirection), StepGenerator::MOVE_TARGET_REL_END_POSN);
		delay(20);
		m_motor.PositionRefSet(0);
		m_lastCommandedPosition = 0;
		return true;
	}
	return false;
}

void MachineAxis::Disable() {
	m_motor.EnableRequest(false);
}

void MachineAxis::PrintReadyState(ClearCore::MotorDriver::MotorReadyStates readyState) const {
	switch (readyState) {
	case ClearCore::MotorDriver::MotorReadyStates::MOTOR_DISABLED:
		Serial.println("Motor Disabled");
		break;
	case ClearCore::MotorDriver::MotorReadyStates::MOTOR_ENABLING:
		Serial.println("Motor Enabling");
		break;
	case ClearCore::MotorDriver::MotorReadyStates::MOTOR_FAULTED:
		Serial.println("Motor Faulted");
		break;
	case ClearCore::MotorDriver::MotorReadyStates::MOTOR_READY:
		Serial.println("Motor Ready");
		break;
	case ClearCore::MotorDriver::MotorReadyStates::MOTOR_MOVING:
		Serial.println("Motor Moving");
		break;
	default:
		Serial.println("Motor Ready State Unknown");
		break;
	}
}

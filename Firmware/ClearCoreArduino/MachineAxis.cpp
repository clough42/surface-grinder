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
    m_motor.EStopConnector(m_eStopPin);
    m_motor.EnableRequest(true);
    m_motor.VelMax(MAX_VELOCITY);
    m_motor.AccelMax(MAX_ACCELERATION);
    m_motor.MoveStopDecel(0);
}

void MachineAxis::MoveToPositionNm(int32_t positionInNanometers) {
    int64_t motorSteps = (static_cast<int64_t>(positionInNanometers) * m_stepsPerNmNumerator) / m_stepsPerNmDenominator;
    m_motor.Move(static_cast<int32_t>(motorSteps) * static_cast<int>(m_motorDirection), StepGenerator::MOVE_TARGET_ABSOLUTE);
    m_lastCommandedPosition = positionInNanometers;
}

void MachineAxis::JogNm(int32_t distanceInNanometers)
{
	MoveToPositionNm(m_lastCommandedPosition + distanceInNanometers);
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

bool MachineAxis::IsMoveComplete() const {
    return m_motor.StepsComplete();
}

void MachineAxis::ResetAndEnable() {
    m_lastCommandedPosition = GetCurrentPositionNm();
    m_motor.ClearAlerts();
	m_motor.EnableRequest(true);
}
// Copyright (c) 2024 James Clough (Clough42, LLC)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the Clough42, LLC nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

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
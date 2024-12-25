// Copyright (c) 2024 James Clough (Clough42, LLC)
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

#include "CycleFlatGrind.h"

#include <ClearCore.h>

void CycleFlatGrind::Reset() {
    Cycle::ClearError();
    currentState = INITIAL;
}

void CycleFlatGrind::Cancel() {
    m_axes[AXIS_X].Stop();
	m_axes[AXIS_Y].Stop();
	m_axes[AXIS_Z].Stop();
}

bool CycleFlatGrind::CanRun() {
    if (!m_axes[AXIS_X].IsHomed()) {
        Cycle::SetError("HOME machine before grindingF");
        return false;
    }
    if (!m_config.GetProcessValues(Axis::X)->startLimit.HasValue() ||
        !m_config.GetProcessValues(Axis::X)->endLimit.HasValue() ||
        !m_config.GetProcessValues(Axis::Z)->startLimit.HasValue() ||
        !m_config.GetProcessValues(Axis::Z)->endLimit.HasValue() ||
        !m_config.GetProcessValues(Axis::Y)->workPosition.HasValue() ||
        !m_config.GetProcessValues(Axis::Y)->safePosition.HasValue()
        ) {
        Cycle::SetError("START and END limits, WORK and\nSAFE heights must be set");
        return false;
    }
}

bool CycleFlatGrind::AllowJog(Axis axis, int32_t nanometers) const {
    // no jogging allowed
    return false;
}

/////////////////////////////////////////////////////////////////////////
// STATE MACHINE
/////////////////////////////////////////////////////////////////////////

bool CycleFlatGrind::Update() {
    if (!CanRun()) {
        return false;
    }

    switch (currentState) {
	case INITIAL:
		UpdateInitial();
		break;
    case RISE_TO_SAFE:
		UpdateRiseToSafe();
		break;
	case MOVE_TO_START:
		UpdateMoveToStart();
		break;
	case LOWER_TO_WORK:
		UpdateLowerToWork();
		break;
	case GRIND_TO_END_X:
		UpdateGrindToEndX();
		break;
	case ADVANCE_Z_AT_END:
		UpdateAdvanceZAtEnd();
		break;
	case GRIND_TO_START_X:
		UpdateGrindToStartX();
		break;
	case ADVANCE_Z_AT_START:
		UpdateAdvanceZAtStart();
		break;
	case REWIND_Z:
		UpdateRewindZ();
		break;
    case FINAL:
        return false; // we be done
    }

    return true; // never ends
}

void CycleFlatGrind::UpdateInitial() {
	// if we're already at the start position, skip the rise
	if (CloseEnoughTo(m_config.GetProcessValues(Axis::X)->startLimit.Value(), m_config.GetProcessValues(Axis::Z)->startLimit.Value())) {
		TransitionToMoveToStart();
		return;
	}

	// otherwise, we have to rise to the safe position to traverse to start
	TransitionToRiseToSafe();
}

void CycleFlatGrind::TransitionToRiseToSafe() {
	Serial.println("FlatGrind: Rising to Safe");
	m_axes[AXIS_Y].MoveToPositionNm(m_config.GetProcessValues(Axis::Y)->safePosition.Value(), m_config.GetAxisConfig(Axis::Y)->traverseSpeedMmM);
	currentState = RISE_TO_SAFE;
}

void CycleFlatGrind::UpdateRiseToSafe() {
	if (m_axes[AXIS_Y].MoveComplete()) {
		TransitionToMoveToStart();
	}
}

void CycleFlatGrind::TransitionToMoveToStart() {
	Serial.println("FlatGrind: Moving to Start");
	m_axes[AXIS_X].MoveToPositionNm(m_config.GetProcessValues(Axis::X)->startLimit.Value(), m_config.GetAxisConfig(Axis::X)->traverseSpeedMmM);
	m_axes[AXIS_Z].MoveToPositionNm(m_config.GetProcessValues(Axis::Z)->startLimit.Value(), m_config.GetAxisConfig(Axis::Z)->traverseSpeedMmM);
	currentState = MOVE_TO_START;
}

void CycleFlatGrind::UpdateMoveToStart() {
	if (m_axes[AXIS_X].MoveComplete() && m_axes[AXIS_Z].MoveComplete()) {
		TransitionToLowerToWork();
	}
}

void CycleFlatGrind::TransitionToLowerToWork() {
	Serial.println("FlatGrind: Lowering to Work");
	m_axes[AXIS_Y].MoveToPositionNm(m_config.GetProcessValues(Axis::Y)->workPosition.Value(), m_config.GetAxisConfig(Axis::Y)->traverseSpeedMmM);
	currentState = LOWER_TO_WORK;
}

void CycleFlatGrind::UpdateLowerToWork() {
	if (m_axes[AXIS_Y].MoveComplete()) {
		TransitionToGrindToEndX();
	}
}

void CycleFlatGrind::TransitionToGrindToEndX() {
	Serial.println("FlatGrind: Grinding to end X");
	m_axes[AXIS_X].MoveToPositionNm(m_config.GetProcessValues(Axis::X)->endLimit.Value(), m_config.GetProcessValues(Axis::X)->grindSpeedMmM);
	currentState = GRIND_TO_END_X;
}

void CycleFlatGrind::UpdateGrindToEndX() {
	if (m_axes[AXIS_X].MoveComplete()) {
		TransitionToAdvanceZAtEnd();
	}
}

void CycleFlatGrind::TransitionToAdvanceZAtEnd() {
	int32_t zMoveNm = CalculateZAdvance();

	// if there's nothing left to do, just grind back to start
	if (zMoveNm == 0) {
		TransitionToGrindToStartX();
		return;
	}

	Serial.println("FlatGrind: Advaincing Z (at end X)");
	m_axes[AXIS_Z].MoveToPositionNm(m_axes[AXIS_Z].GetCurrentPositionNm() + zMoveNm, m_config.GetAxisConfig(Axis::Z)->traverseSpeedMmM);
	currentState = ADVANCE_Z_AT_END;
}

void CycleFlatGrind::UpdateAdvanceZAtEnd() {
	if (m_axes[AXIS_Z].MoveComplete()) {
		TransitionToGrindToStartX();
	}
}

void CycleFlatGrind::TransitionToGrindToStartX() {
	Serial.println("FlatGrind: Grinding to start X");
	m_axes[AXIS_X].MoveToPositionNm(m_config.GetProcessValues(Axis::X)->startLimit.Value(), m_config.GetProcessValues(Axis::X)->grindSpeedMmM);
	currentState = GRIND_TO_START_X;
}

void CycleFlatGrind::UpdateGrindToStartX() {
	if (m_axes[AXIS_X].MoveComplete()) {
		TransitionToAdvanceZAtStart();
	}
}

void CycleFlatGrind::TransitionToAdvanceZAtStart() {
	int32_t zMoveNm = CalculateZAdvance();

	// if there's nothing left to do, rewind Z instead
	if (zMoveNm == 0) {
		TransitionToRewindZ();
		return;
	}

	Serial.println("FlatGrind: Advancing Z (at start X)");
	m_axes[AXIS_Z].MoveToPositionNm(m_axes[AXIS_Z].GetCurrentPositionNm() + zMoveNm, m_config.GetAxisConfig(Axis::Z)->traverseSpeedMmM);
	currentState = ADVANCE_Z_AT_START;
}

void CycleFlatGrind::UpdateAdvanceZAtStart() {
	if (m_axes[AXIS_Z].MoveComplete()) {
		TransitionToGrindToEndX();
	}
}

void CycleFlatGrind::TransitionToRewindZ() {
	Serial.println("FlatGrind: Rewinding Z");
	m_axes[AXIS_Z].MoveToPositionNm(m_config.GetProcessValues(Axis::Z)->startLimit.Value(), m_config.GetAxisConfig(Axis::Z)->traverseSpeedMmM);
	currentState = REWIND_Z;
}

void CycleFlatGrind::UpdateRewindZ() {
	if (m_axes[AXIS_Z].MoveComplete()) {
		TransitionToFinal();
	}
}

void CycleFlatGrind::TransitionToFinal() {
	Serial.println("FlatGrind: Done");
	currentState = FINAL;
}

int32_t CycleFlatGrind::CalculateZAdvance() {
	int32_t currentZ = m_axes[AXIS_Z].GetCurrentPositionNm();
	int32_t targetZ = m_config.GetProcessValues(Axis::Z)->endLimit.Value();
	targetZ = m_axes[AXIS_Z].QuantizePositionNm(targetZ); // quantize so we can compare
	int32_t zAdvance = targetZ - currentZ;

	Serial.print("ZAdvance: ");
	Serial.println(zAdvance);

	// limit it to the stepover
	int32_t stepoverNm = m_config.GetProcessValues(Axis::Z)->grindingStepoverNm;
	if (zAdvance > stepoverNm) zAdvance = stepoverNm;
	if (zAdvance < -stepoverNm) zAdvance = -stepoverNm;

	Serial.print("ZAdvance (limited): ");
	Serial.println(zAdvance);

	return zAdvance;
}

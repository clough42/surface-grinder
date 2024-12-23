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

#include "CycleTouchoff.h"

#include <ClearCore.h>

void CycleTouchoff::Reset() {
	Cycle::ClearError();
    currentState = INITIAL;
}

bool CycleTouchoff::CanRun() {
	if (! m_axes[AXIS_X].IsHomed()) {
		Cycle::SetError("HOME machine before running TOUCH-OFF");
		return false;
	}
    if (!m_config.GetProcessValues(Axis::X)->startLimit.HasValue() ||
        !m_config.GetProcessValues(Axis::X)->endLimit.HasValue()) {
		Cycle::SetError("X START and END limits not set");
        return false;
    }
}

bool CycleTouchoff::AllowJog(Axis axis, int32_t nanometers) const {
    // allow jogging in Z
    if (axis == Axis::Z) return true;

    // allow only fine jogging in Y
	if (axis == Axis::Y && nanometers <= 2540) return true;

    return false;
}

/////////////////////////////////////////////////////////////////////////
// STATE MACHINE
/////////////////////////////////////////////////////////////////////////

bool CycleTouchoff::Update() {
	if (!CanRun()) {
		return false;
	}

    switch (currentState) {
    case INITIAL:
        UpdateInitial();
        break;
    case MOVE_TO_X_START_LIMIT:
        UpdateMoveToXStartLimit();
        break;
    case MOVE_TO_X_END_LIMIT:
        UpdateMoveToXEndLimit();
        break;
    }

    return true; // never ends
}

void CycleTouchoff::UpdateInitial() {
    TransitionToMoveToXStartLimit();
}

void CycleTouchoff::TransitionToMoveToXStartLimit() {
    Serial.println("Moving to X Start");
	Configuration::ProcessValues* processValues = m_config.GetProcessValues(Axis::X);
    m_axes[AXIS_X].MoveToPositionNm(processValues->startLimit.Value(), processValues->grindSpeedMmM);
    currentState = MOVE_TO_X_START_LIMIT;
}

void CycleTouchoff::UpdateMoveToXStartLimit() {
    // if motion is complete
    if (m_axes[AXIS_X].MoveComplete()) {
        TransitionToMoveToXEndLimit();
    }
}

void CycleTouchoff::TransitionToMoveToXEndLimit() {
    Serial.println("Moving to X End");
	Configuration::ProcessValues* processValues = m_config.GetProcessValues(Axis::X);
    m_axes[AXIS_X].MoveToPositionNm(processValues->endLimit.Value(), processValues->grindSpeedMmM);
    currentState = MOVE_TO_X_END_LIMIT;
}

void CycleTouchoff::UpdateMoveToXEndLimit() {
    // if motion is complete
    if (m_axes[AXIS_X].MoveComplete()) {
        TransitionToMoveToXStartLimit();
    }
}


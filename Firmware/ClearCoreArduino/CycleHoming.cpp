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

#include "CycleHoming.h"
#include "CommonEnums.h"

#include <ClearCore.h>

void CycleHoming::Reset() {
    Cycle::ClearError();
    currentState = INITIAL;
}

void CycleHoming::Cancel() {
	for (int i = 0; i < AXIS_COUNT; i++) {
		m_axes[i].Stop();
	}
}

bool CycleHoming::CanRun() {
    return true;
}

/////////////////////////////////////////////////////////////////////////
// STATE MACHINE
/////////////////////////////////////////////////////////////////////////

bool CycleHoming::Update() {
    switch (currentState) {
    case INITIAL:
        UpdateInitial();
        break;
    case HOME_Y:
        UpdateHomeY();
        break;
    case HOME_Z:
        UpdateHomeZ();
        break;
    case HOME_X:
        UpdateHomeX();
        break;
    case FINAL:
        return false;
    }

    return true; // still more work to do
}

void CycleHoming::UpdateInitial() {
    TransitionToHomeY();
}

void CycleHoming::TransitionToHomeY() {
    Serial.println("Homing Y");
	m_axes[AXIS_Y].StartHomingCycle();
    currentState = HOME_Y;
}

void CycleHoming::UpdateHomeY() {
    // if Y home is complete
    if (m_axes[AXIS_Y].IsHomingCycleComplete()) {
        TransitionToHomeZ();
    }
}

void CycleHoming::TransitionToHomeZ() {
    Serial.println("Homing Z");
    m_axes[AXIS_Z].StartHomingCycle();
    currentState = HOME_Z;
}

void CycleHoming::UpdateHomeZ() {
    // if Z home is complete
    if (m_axes[AXIS_Z].IsHomingCycleComplete()) {
        TransitionToHomeX();
    }
}

void CycleHoming::TransitionToHomeX() {
    Serial.println("Homing X");
    m_axes[AXIS_X].StartHomingCycle();
    currentState = HOME_X;
}

void CycleHoming::UpdateHomeX() {
    // if X home is complete
    if (m_axes[AXIS_X].IsHomingCycleComplete()) {
        TransitionToFinal();
    }
}

void CycleHoming::TransitionToFinal() {
    Serial.println("Homing complete");
    currentState = FINAL;
}


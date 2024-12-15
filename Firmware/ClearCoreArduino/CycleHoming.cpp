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

#include "CycleHoming.h"

#include <ClearCore.h>

void CycleHoming::Reset() {
    m_isInError = false;
    currentState = INITIAL;
}

bool CycleHoming::IsInError() {
    return m_isInError;
}

/////////////////////////////////////////////////////////////////////////
// STATE MACHINE
/////////////////////////////////////////////////////////////////////////

bool CycleHoming::Update() {

	//Serial.println("CycleHoming::Update()");
    switch (currentState) {
    case INITIAL:
        UpdateInitial();
        break;
    case DISABLING:
        UpdateDisabling();
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
    TransitionToDisabling();
}

void CycleHoming::TransitionToDisabling() {
    Serial.println("Disabling motors");
    for (int i = 0; i < AXIS_COUNT; ++i) {
        m_axes[i].Disable();
    }
    currentState = DISABLING;
}

void CycleHoming::UpdateDisabling() {
    // if all motors are disabled
    if (m_axes[AXIS_X].IsDisabled() &&
        m_axes[AXIS_Y].IsDisabled() &&
        m_axes[AXIS_Z].IsDisabled()) {
        TransitionToHomeY();
    }
}

void CycleHoming::TransitionToHomeY() {
    Serial.println("Homing Y");
    StartHomingAxis(AXIS_Y);
    currentState = HOME_Y;
}

void CycleHoming::UpdateHomeY() {
    // if Y home is complete
    if (m_axes[AXIS_Y].IsReady()) {
        m_axes[AXIS_Y].StopAndReference();
        TransitionToHomeZ();
    }
}

void CycleHoming::TransitionToHomeZ() {
    Serial.println("Homing Z");
    StartHomingAxis(AXIS_Z);
    currentState = HOME_Z;
}

void CycleHoming::UpdateHomeZ() {
    // if Z home is complete
    if (m_axes[AXIS_Z].IsReady()) {
        m_axes[AXIS_Z].StopAndReference();
        TransitionToHomeX();
    }
}

void CycleHoming::TransitionToHomeX() {
    Serial.println("Homing X");
    StartHomingAxis(AXIS_X);
    currentState = HOME_X;
}

void CycleHoming::UpdateHomeX() {
    // if X home is complete
    if (m_axes[AXIS_X].IsReady()) {
        m_axes[AXIS_X].StopAndReference();
        TransitionToFinal();
    }
}

void CycleHoming::TransitionToFinal() {
    Serial.println("Homing complete");
    currentState = FINAL;
}


// utility methods

void CycleHoming::StartHomingAxis(int axis) {
    Serial.println("Start Homing Axis");
    //m_axes[axis].ResetAndEnable();
    m_axes[axis].SeekHome();
}
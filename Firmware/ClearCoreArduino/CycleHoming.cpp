// CycleHoming.cpp
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
// CycleHoming.h
#ifndef CYCLEHOMING_H
#define CYCLEHOMING_H

#include <Arduino.h>
#include "Cycle.h"
#include "MachineAxis.h"

class CycleHoming : public Cycle {
public:
    // Define the states of the state machine
    enum HomingState {
        UNKNOWN,
        DISABLING,
        HOME_Y,
        HOME_Z,
        HOME_X,
        HOMED
    };

    // Constructor
	CycleHoming(MachineAxis* axes[AXIS_COUNT]) : currentState(UNKNOWN) {
        for (int i = 0; i < AXIS_COUNT; ++i) {
            m_axes[i] = axes[i];
        }
    }

	void Reset() override;
    bool IsInError() override;
    bool Update() override;

private:
    HomingState currentState;
	MachineAxis* m_axes[AXIS_COUNT];

    // Transition methods for each state
    void TransitionToUnknown();
    void TransitionToDisabling();
    void TransitionToHomeY();
    void TransitionToHomeZ();
    void TransitionToHomeX();
    void TransitionToHomed();

    // Update methods for each state
    void UpdateUnknown();
    void UpdateDisabling();
    void UpdateHomeY();
    void UpdateHomeZ();
    void UpdateHomeX();

    // utility methods
    void StartHomingAxis(int axis);

    bool m_isInError = false;
};

#endif // CYCLEHOMING_H
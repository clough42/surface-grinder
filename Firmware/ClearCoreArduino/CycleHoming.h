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
        INITIAL,
        DISABLING,
        HOME_Y,
        HOME_Z,
        HOME_X,
        FINAL
    };

    // Constructor
	CycleHoming(MachineAxis* axes) 
        : m_axes(axes), Cycle(Mode::SETUP), currentState(INITIAL) { }

	void Reset() override;
    bool IsInError() override;
    bool Update() override;

private:
    HomingState currentState;
	MachineAxis* m_axes;

    // Transition methods for each state
    void TransitionToDisabling();
    void TransitionToHomeY();
    void TransitionToHomeZ();
    void TransitionToHomeX();
    void TransitionToFinal();

    // Update methods for each state
    void UpdateInitial();
    void UpdateDisabling();
    void UpdateHomeY();
    void UpdateHomeZ();
    void UpdateHomeX();

    // utility methods
    void StartHomingAxis(int axis);

    bool m_isInError = false;
};

#endif // CYCLEHOMING_H
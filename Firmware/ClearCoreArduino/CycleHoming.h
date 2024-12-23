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
        HOME_Y,
        HOME_Z,
        HOME_X,
        FINAL
    };

    // Constructor
	CycleHoming(MachineAxis* axes) 
        : m_axes(axes), Cycle(CycleType::HOME), currentState(INITIAL) { }

	void Reset() override;
	bool CanRun() override;
    bool Update() override;

private:
    HomingState currentState;
	MachineAxis* m_axes;

    // Transition methods for each state
    void TransitionToHomeY();
    void TransitionToHomeZ();
    void TransitionToHomeX();
    void TransitionToFinal();

    // Update methods for each state
    void UpdateInitial();
    void UpdateHomeY();
    void UpdateHomeZ();
    void UpdateHomeX();
};

#endif // CYCLEHOMING_H
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

#ifndef CYCLETOUCHOFF_H
#define CYCLETOUCHOFF_H

#include <Arduino.h>
#include "Cycle.h"
#include "MachineAxis.h"

class CycleTouchoff : public Cycle {
public:
    // Define the states of the state machine
    enum TouchoffState {
        INITIAL,
        MOVE_TO_X_START_LIMIT,
        MOVE_TO_X_END_LIMIT
    };

    // Constructor
    CycleTouchoff(MachineAxis* axes, Configuration& config)
        : Cycle(CycleType::TOUCHOFF), m_axes(axes), m_config(config), currentState(INITIAL) { }

    void Reset() override;
	bool CanRun() override;
    bool Update() override;
    void Cancel() override;
	bool AllowJog(Axis axis, int32_t nanometers) const override;

private:
    TouchoffState currentState;
    MachineAxis* m_axes;
	Configuration& m_config;

    // Transition methods for each state
	void TransitionToMoveToXStartLimit();
    void TransitionToMoveToXEndLimit();

    // Update methods for each state
    void UpdateInitial();
    void UpdateMoveToXStartLimit();
    void UpdateMoveToXEndLimit();
};

#endif // CYCLETOUCHOFF_H
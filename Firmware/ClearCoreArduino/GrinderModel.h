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

#ifndef GRINDER_MODEL_H
#define GRINDER_MODEL_H

#include "MachineAxis.h"
#include "Cycle.h"
#include "CommonEnums.h"

class GrinderModel {
public:
    // Constructor that takes an array of three MachineAxis objects
	GrinderModel(MachineAxis* axes, Cycle *cycles[], int cycleCount, DigitalInOut& leftLimit, DigitalInOut& rightLimit)
		: m_axes(axes), m_cycles(cycles), m_cycleCount(cycleCount), m_leftLimit(leftLimit), m_rightLimit(rightLimit), m_error(Optional<const char*>()) {}

    // Method to initialize all axes
    void Init();

    // Method to update all axes
	void Update();

	Status GetStatus() const {
		return m_status;
	}

	bool IsHomed() const;

	bool CycleStart(CycleType cycleType);

	bool CycleStop();

	int32_t GetCurrentPositionNm(Axis axis) const;

	void JogAxisNm(Axis axis, int32_t distanceInNanometers);

	void MoveToPosition(Axis axis, int32_t positionInNanometers);

	void EStop();

	Optional<const char*> Error() {
		return m_error;
	}

	bool AllowJog(Axis axis) const;

private:
	Status m_status = Status::IDLE;
    MachineAxis *m_axes;
	Cycle** m_cycles;
	int m_cycleCount;
	Cycle* m_currentCycle = nullptr;
	DigitalInOut& m_leftLimit;
	DigitalInOut& m_rightLimit;

	Optional<const char*> m_error;
};

#endif // GRINDER_MODEL_H

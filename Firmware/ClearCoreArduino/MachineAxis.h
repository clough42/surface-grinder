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

#ifndef MACHINE_AXIS_H
#define MACHINE_AXIS_H

#include <cstdint>
#include "ClearCore.h" // Include the ClearCore library
#include "CommonEnums.h"

#define STEPS_PER_REV 1000
#define SECONDS_PER_MINUTE 60
#define RPM * STEPS_PER_REV / SECONDS_PER_MINUTE
#define MAX_VELOCITY 1000 RPM
#define MAX_ACCELERATION 50000

class MachineAxis {
public:

    MachineAxis(MotorDriver& motor, int32_t stepsPerNmNumerator, int32_t stepsPerNmDenominator, ClearCorePins eStopPin, Direction motorDirection = Direction::NORMAL)
        : m_stepsPerNmNumerator(stepsPerNmNumerator), m_stepsPerNmDenominator(stepsPerNmDenominator), m_motor(motor), m_eStopPin(eStopPin), m_motorDirection(motorDirection) {}

    void Init();
    void MoveToPositionNm(int32_t positionInNanometers);
	void JogNm(int32_t distanceInNanometers);
    int32_t GetCurrentPositionNm() const;
    int32_t GetLastCommandedPositionNm() const;
    bool IsReady() const;
    bool IsDisabled() const;

    void StartHomingCycle();
    bool IsHomingCycleComplete();

    void Disable();
    void ResetAndEnable();
    void SeekHome();
    void StopAndReference();

private:
	void PrintReadyState(ClearCore::MotorDriver::MotorReadyStates readyState) const;

    // Ratio of nanometers to motor steps
    int32_t m_stepsPerNmNumerator;
    int32_t m_stepsPerNmDenominator;

    // The motor driver to use for this axis
    MotorDriver &m_motor;

    // Direction config
    Direction m_motorDirection;

    // EStop pin
    ClearCorePins m_eStopPin;

    // Last commanded position in nanometers
    int32_t m_lastCommandedPosition;
};

#endif // MACHINE_AXIS_H

// Copyright (c) 2024 James Clough (Clough42, LLC)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the Clough42, LLC nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

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
    bool IsMoveComplete() const;
    void ResetAndEnable();

private:
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

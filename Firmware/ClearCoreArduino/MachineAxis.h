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

#ifndef MACHINE_AXIS_H
#define MACHINE_AXIS_H

#include <cstdint>
#include "ClearCore.h" // Include the ClearCore library
#include "CommonEnums.h"
#include "Configuration.h"
#include "Limiter.h"

class MachineAxis {
public:

    MachineAxis(MotorDriver& motor, ClearCorePins eStopPin, Configuration::AxisConfig *config) :
        m_stepsPerNmNumerator(config->stepsPerNmNumerator), 
        m_stepsPerNmDenominator(config->stepsPerNmDenominator), 
        m_motor(motor), m_eStopPin(eStopPin),
		m_axisConfig(config),
		m_isHomed(false),
        m_positionLimiter(0,0) {}

    void Init();
	void MoveToPositionNm(int32_t positionInNanometers);
    void MoveToPositionNm(int32_t positionInNanometers, int32_t speedMmM);
	void JogNm(int32_t distanceInNanometers);
    void Stop();
    int32_t GetCurrentPositionNm() const;
    int32_t GetLastCommandedPositionNm() const;
	int32_t QuantizePositionNm(int32_t positionInNanometers) const;
    bool MoveComplete();
    bool IsInError() const;
    
    // homing
    void StartHomingCycle();
    bool IsHomingCycleComplete();
	bool IsHomed() const { return m_isHomed; }

    void Disable();

private:
    int32_t CalculateMotorStepsDirectional(int64_t positionInNanometers) const;
	int32_t CalculateMotorStepsAbsolute(int64_t positionInNanometers) const;
	void PrintReadyState(ClearCore::MotorDriver::MotorReadyStates readyState) const;
    int32_t CalculateVelocity(int32_t speedMmM) const;
    bool HlfbAsserted() const;

    // Ratio of nanometers to motor steps
    int32_t m_stepsPerNmNumerator;
    int32_t m_stepsPerNmDenominator;

    // The motor driver to use for this axis
    MotorDriver &m_motor;

    // Configuration
    Configuration::AxisConfig* m_axisConfig;

    // EStop pin
    ClearCorePins m_eStopPin;

    // Last commanded position in nanometers
    int32_t m_lastCommandedPosition;

    // flag to track whether this axis is homed
    bool m_isHomed;

    Limiter<int32_t> m_positionLimiter;
};

#endif // MACHINE_AXIS_H

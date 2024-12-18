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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SPI.h>
#include <SD.h>

#include "ClearCore.h"
#include "CommonEnums.h"

class Configuration {
public:
    struct AxisConfig {
        int32_t stepsPerNmNumerator;
        int32_t stepsPerNmDenominator;
        int32_t homingSpeedMmM;
        int64_t homingBackoffNm;
        int64_t totalTravelNm;
        Direction motorDirection;   // Direction of motor vs handwheel
		Direction droDirection;     // Direction of DRO vs handwheel
		Direction homingDirection;  // Direction of handwheel for homing
    };

    Configuration(const char* filename) : m_filename(filename) {};

    AxisConfig* GetAxisConfig(Axis axis) { return &axisConfigs[static_cast<int>(axis)]; }

    //bool Load();
    //bool Save();

private:
    const char* m_filename;

    // Machine configuration values
    AxisConfig axisConfigs[AXIS_COUNT] = {
        {
            .stepsPerNmNumerator = 3,
            .stepsPerNmDenominator = 130175,
            .homingSpeedMmM = 1000,
            .homingBackoffNm = 5 * 1000 * 1000,
            .totalTravelNm = 482 * 1000 * 1000,
            .motorDirection = Direction::NEGATIVE,
            .droDirection = Direction::NEGATIVE,
            .homingDirection = Direction::POSITIVE
        },
        {
            .stepsPerNmNumerator = 6,
            .stepsPerNmDenominator = 3175,
            .homingSpeedMmM = 300,
            .homingBackoffNm = 1 * 1000 * 1000,
            .totalTravelNm = 310 * 1000 * 1000,
            .motorDirection = Direction::NEGATIVE,
            .droDirection = Direction::POSITIVE,
            .homingDirection = Direction::POSITIVE
        },
        {
            .stepsPerNmNumerator = 3,
            .stepsPerNmDenominator = 6350,
            .homingSpeedMmM = 1000,
            .homingBackoffNm = 1 * 1000 * 1000,
            .totalTravelNm = 180 * 1000 * 1000,
            .motorDirection = Direction::NEGATIVE,
            .droDirection = Direction::NEGATIVE,
            .homingDirection = Direction::NEGATIVE
        }
    };

    // UI Configuration
    Units units;

    // Process Settings
    int32_t droWorkOffsets[AXIS_COUNT] = { 0, 0, 0 };
    int32_t startLimits[AXIS_COUNT] = { 0, 0, 0 };
    int32_t endLimits[AXIS_COUNT] = { 0, 0, 0 };

};

#endif // CONFIGURATION_H

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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SPI.h>
#include <SD.h>

#include "ClearCore.h"
#include "CommonEnums.h"
#include "TrackedValue.h"
#include "Optional.h"

class Configuration {
public:
    struct AxisConfig {
        int32_t stepsPerNmNumerator;
        int32_t stepsPerNmDenominator;
        int32_t homingSpeedMmM;
        int32_t jogSpeedMmM;
        int32_t traverseSpeedMmM;
        int32_t acceleration;
        int64_t homingBackoffNm;
        int64_t totalTravelNm;
        Direction motorDirection;   // Direction of motor vs handwheel
		Direction droDirection;     // Direction of DRO vs handwheel
		Direction homingDirection;  // Direction of handwheel for homing
    };

    struct ProcessValues {
        int32_t droWorkOffset;
        int32_t grindSpeedMmM;
        int32_t grindingStepoverNm;
        Optional<int32_t> startLimit;
        Optional<int32_t> endLimit;
        Optional<int32_t> safePosition;
        Optional<int32_t> workPosition;

    };

    struct GrindCycleParameters {
 		int32_t roughPassDepthIndex;
        int32_t finishPassDepthIndex;
        int16_t roughPassCount;
        int16_t finishPassCount;
        int16_t sparkPassCount;
        bool autoAdvance;
    };

    struct UIParameters {
        Units units;
        uint8_t hmiContrast;
    };

#define GRIND_DEPTHS_COUNT 6
    struct PredefinedGrindDepths {
        int32_t RoughInchDepthsNm[GRIND_DEPTHS_COUNT];
        int32_t RoughMmDepthsNm[GRIND_DEPTHS_COUNT];
        int32_t FinishInchDepthsNm[GRIND_DEPTHS_COUNT];
        int32_t FinishMmDepthsNm[GRIND_DEPTHS_COUNT];
    };

    Configuration(const char* filename) : m_filename(filename) {};

    AxisConfig* GetAxisConfig(Axis axis) { return &axisConfigs[static_cast<int>(axis)]; }
	ProcessValues* GetProcessValues(Axis axis) { return &processValues[static_cast<int>(axis)]; }
	GrindCycleParameters* GetFlatGrindParams() { return &flatGrindParams; }
	UIParameters* GetUIParams() { return &uiParams; }
	PredefinedGrindDepths* GetGrindDepths() { return &grindDepths; }

    int32_t GetRoughFeedNm() {
        if (uiParams.units == Units::INCHES) {
            return grindDepths.RoughInchDepthsNm[flatGrindParams.roughPassDepthIndex];
        }
        if (uiParams.units == Units::MILLIMETERS) {
            return grindDepths.RoughMmDepthsNm[flatGrindParams.roughPassDepthIndex];
        }
        return 0;
    }

    int32_t GetFinishFeedNm() {
        if (uiParams.units == Units::INCHES) {
            return grindDepths.FinishInchDepthsNm[flatGrindParams.finishPassDepthIndex];
        }
        if (uiParams.units == Units::MILLIMETERS) {
            return grindDepths.FinishMmDepthsNm[flatGrindParams.finishPassDepthIndex];
        }
        return 0;
    }

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
            .jogSpeedMmM = 30000,
            .traverseSpeedMmM = 5000,
            .acceleration = 50000,
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
            .jogSpeedMmM = 425,
            .traverseSpeedMmM = 300,
            .acceleration = 50000,
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
            .jogSpeedMmM = 1800,
            .traverseSpeedMmM = 1000,
            .acceleration = 50000,
            .homingBackoffNm = 1 * 1000 * 1000,
            .totalTravelNm = 180 * 1000 * 1000,
            .motorDirection = Direction::NEGATIVE,
            .droDirection = Direction::NEGATIVE,
            .homingDirection = Direction::NEGATIVE
        }
    };

    // Optional values are initialized using default constructors
    ProcessValues processValues[AXIS_COUNT] = {
        {
            .droWorkOffset = 0,
            .grindSpeedMmM = 15240 // 50fpm = 15240mm/min
        },
        {
            .droWorkOffset = 0,
            .grindSpeedMmM = 0, // do we ever even want to do this?
			.grindingStepoverNm = 3175000 // 1/8" = 3175000nm
        },
        {
            .droWorkOffset = 0,
			.grindSpeedMmM = 100, // very slow; figure out reasonable values later
            .grindingStepoverNm = 3175000 // 1/8" = 3175000nm
        }
    };

	GrindCycleParameters flatGrindParams = {
		.roughPassDepthIndex = 1,
		.finishPassDepthIndex = 3,
		.roughPassCount = 0,
		.finishPassCount = 0,
		.sparkPassCount = 0,
		.autoAdvance = false
	};

    // UI Configuration
    UIParameters uiParams = {
        .units = Units::INCHES,
		.hmiContrast = 15
    };

    PredefinedGrindDepths grindDepths = {
		.RoughInchDepthsNm = {
            12700,  // 0.0005"
            25400,  // 0.001"
			38100,  // 0.0015"
			50800,  // 0.002"
			63500,  // 0.0025"
			76200   // 0.003"
        },
		.RoughMmDepthsNm = { 
            10000,  // 0.01mm 
            20000,  // 0.02mm 
            30000,  // 0.03mm 
            40000,  // 0.04mm 
            50000,  // 0.05mm 
			60000   // 0.06mm
        },
		.FinishInchDepthsNm = {
			1270,   // 0.00005"
			2540,   // 0.0001"
			3810,   // 0.00015"
			5080,   // 0.0002"
			7620,   // 0.0003"
			12700   // 0.0005"
        },
		.FinishMmDepthsNm = {
            1000,   // 0.001mm
			2000,   // 0.002mm
			3000,   // 0.003mm
			5000,   // 0.005mm
            7500,   // 0.0075mm   
			10000   // 0.01mm
        }
	};

};



#endif // CONFIGURATION_H

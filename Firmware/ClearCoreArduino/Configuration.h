#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ClearCore.h"
#include "CommonEnums.h"

class Configuration {
public:
    Configuration(const char* filename) : m_filename(filename) {};

    bool Load();
    bool Save();

    // Property accessors
    int GetSomeIntValue() const;
    void SetSomeIntValue(int value);

private:
    const char* m_filename;

	struct AxisConfig {
		int32_t stepsPerNmNumerator;
		int32_t stepsPerNmDenominator;
		Direction motorDirection;
		Direction homingDirection;
	};

    // Machine configuration values
    AxisConfig xAxisConfig = {
            .stepsPerNmNumerator = 3,
            .stepsPerNmDenominator = 130175,
            .motorDirection = Direction::NEGATIVE,
            .homingDirection = Direction::NEGATIVE
    };

    AxisConfig yAxisConfig = {
        .stepsPerNmNumerator = 6,
        .stepsPerNmDenominator = 3175,
        .motorDirection = Direction::NEGATIVE,
        .homingDirection = Direction::POSITIVE
    };

    AxisConfig zAxisConfig = {
        .stepsPerNmNumerator = 3,
        .stepsPerNmDenominator = 6350,
        .motorDirection = Direction::NEGATIVE,
        .homingDirection = Direction::POSITIVE
    };

    // Stored values
    Units units;
    int32_t droWorkOffsets[AXIS_COUNT] = { 0, 0, 0 };
    int32_t startLimits[AXIS_COUNT] = { 0, 0, 0 };
    int32_t endLimits[AXIS_COUNT] = { 0, 0, 0 };

};

#endif // CONFIGURATION_H

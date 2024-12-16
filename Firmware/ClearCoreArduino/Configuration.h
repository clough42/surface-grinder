#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <SPI.h>

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
        Direction motorDirection;
        Direction homingDirection;
    };

    Configuration(const char* filename) : m_filename(filename) {};

    AxisConfig* GetAxisConfig(Axis axis) { return &axisConfigs[static_cast<int>(axis)]; }

    //bool Load();
    //bool Save();

    //// Property accessors
    //int GetSomeIntValue() const;
    //void SetSomeIntValue(int value);

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
            .homingDirection = Direction::NEGATIVE
        },
        {
            .stepsPerNmNumerator = 6,
            .stepsPerNmDenominator = 3175,
            .homingSpeedMmM = 300,
            .homingBackoffNm = 1 * 1000 * 1000,
            .totalTravelNm = 310 * 1000 * 1000,
            .motorDirection = Direction::NEGATIVE,
            .homingDirection = Direction::POSITIVE
        },
        {
            .stepsPerNmNumerator = 3,
            .stepsPerNmDenominator = 6350,
            .homingSpeedMmM = 1000,
            .homingBackoffNm = 1 * 1000 * 1000,
            .totalTravelNm = 180 * 1000 * 1000,
            .motorDirection = Direction::NEGATIVE,
            .homingDirection = Direction::POSITIVE
        }
    };

    // Stored values
    Units units;
    int32_t droWorkOffsets[AXIS_COUNT] = { 0, 0, 0 };
    int32_t startLimits[AXIS_COUNT] = { 0, 0, 0 };
    int32_t endLimits[AXIS_COUNT] = { 0, 0, 0 };

};

#endif // CONFIGURATION_H

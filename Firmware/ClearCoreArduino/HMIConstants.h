// HMIConstants.h
#ifndef __HMICONSTANTS_H__
#define __HMICONSTANTS_H__

namespace HMI {
    // Form 0 - DRO
    constexpr int FORM_DRO = 0;

    constexpr int DRO_DIGITS_X = 0;
    constexpr int DRO_DIGITS_Y = 1;
    constexpr int DRO_DIGITS_Z = 2;

    constexpr int DRO_LED_X = 0;
    constexpr int DRO_LED_Y = 1;
    constexpr int DRO_LED_Z = 2;

    constexpr int DRO_LED_1S = 3;
    constexpr int DRO_LED_10S = 4;
    constexpr int DRO_LED_100S = 5;
    constexpr int DRO_LED_1000S = 6;

    constexpr int DRO_ZERO_BUTTON_X = 0;
    constexpr int DRO_ZERO_BUTTON_Y = 1;
    constexpr int DRO_ZERO_BUTTON_Z = 2;

    constexpr int UNITS_BUTTON = 3;
    constexpr int UNITS_BUTTON_VAL_INCH = 0;
    constexpr int UNITS_BUTTON_VAL_MM = 1;

    // Form 1 - Splash
    constexpr int FORM_SPLASH = 1;
}

#endif // __HMICONSTANTS_H__
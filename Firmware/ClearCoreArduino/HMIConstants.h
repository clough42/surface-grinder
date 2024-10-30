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
    constexpr int DRO_LED_10000S = 7;

    constexpr int DRO_ZERO_BUTTON_X = 0;
    constexpr int DRO_ZERO_BUTTON_Y = 1;
    constexpr int DRO_ZERO_BUTTON_Z = 2;

    constexpr int UNITS_BUTTON = 3;
    constexpr int UNITS_BUTTON_VAL_INCH = 0;
    constexpr int UNITS_BUTTON_VAL_MM = 1;

    constexpr int DRO_START_BUTTON_X = 4;
	constexpr int DRO_END_BUTTON_X = 5;
	constexpr int DRO_START_BUTTON_Z = 6;
    constexpr int DRO_END_BUTTON_Z = 7;

    constexpr int DRO_DIGITS_START_X = 3;
	constexpr int DRO_DIGITS_END_X = 4;
	constexpr int DRO_DIGITS_START_Z = 5;
	constexpr int DRO_DIGITS_END_Z = 6;

	constexpr int MODE_BUTTON_SETUP = 8;
	constexpr int MODE_BUTTON_FLAT = 9;
	constexpr int MODE_BUTTON_SIDE = 10;
	constexpr int MODE_BUTTON_CYLINDER = 11;
    constexpr int MODE_BUTTON_DRESS = 12;

    // Form 1 - Splash
    constexpr int FORM_SPLASH = 1;
}

#endif // __HMICONSTANTS_H__
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

    // Form 1 - Splash
    constexpr int FORM_SPLASH = 1;
}

#endif // __HMICONSTANTS_H__
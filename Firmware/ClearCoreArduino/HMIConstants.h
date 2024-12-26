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

#ifndef HMI_CONSTANTS_H
#define HMI_CONSTANTS_H

#include "genieArduinoCLOUGH.h"

namespace HMI {

    constexpr int UNITS_BUTTON_VAL_INCH = 0;
    constexpr int UNITS_BUTTON_VAL_MM = 1;

	// Form 0: SetupMode
	namespace SETUPMODE {

		constexpr int FORM_ID = 0;

		// iLedDigits 0: F0XDro
		constexpr int F0XDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0XDro_ID = 0;

		// iLedDigits 1: F0YDro
		constexpr int F0YDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0YDro_ID = 1;

		// iLedDigits 2: F0ZDro
		constexpr int F0ZDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0ZDro_ID = 2;

		// iLed 0: F0XJog
		constexpr int F0XJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F0XJog_ID = 0;

		// iLed 1: F0YJog
		constexpr int F0YJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F0YJog_ID = 1;

		// iLed 2: F0ZJog
		constexpr int F0ZJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F0ZJog_ID = 2;

		// StaticText 0: F0XLabel
		constexpr int F0XLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F0XLabel_ID = 0;

		// StaticText 1: F0YLabel
		constexpr int F0YLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F0YLabel_ID = 1;

		// StaticText 2: F0ZLabel
		constexpr int F0ZLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F0ZLabel_ID = 2;

		// iLed 3: F0Resolution1
		constexpr int F0Resolution1_TYPE = GENIE_OBJ_ILED;
		constexpr int F0Resolution1_ID = 3;

		// iLed 4: F0Resolution10
		constexpr int F0Resolution10_TYPE = GENIE_OBJ_ILED;
		constexpr int F0Resolution10_ID = 4;

		// iLed 5: F0Resolution100
		constexpr int F0Resolution100_TYPE = GENIE_OBJ_ILED;
		constexpr int F0Resolution100_ID = 5;

		// iLed 6: F0Resolution1000
		constexpr int F0Resolution1000_TYPE = GENIE_OBJ_ILED;
		constexpr int F0Resolution1000_ID = 6;

		// iLed 7: F0Resolution10000
		constexpr int F0Resolution10000_TYPE = GENIE_OBJ_ILED;
		constexpr int F0Resolution10000_ID = 7;

		// iLedDigits 3: F0XStartDRO
		constexpr int F0XStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0XStartDRO_ID = 3;

		// iLedDigits 4: F0XEndDRO
		constexpr int F0XEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0XEndDRO_ID = 4;

		// iLedDigits 5: F0ZStartDRO
		constexpr int F0ZStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0ZStartDRO_ID = 5;

		// iLedDigits 6: F0ZEndDRO
		constexpr int F0ZEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0ZEndDRO_ID = 6;

		// Line 0: F0Line0
		constexpr int F0Line0_TYPE = -1;
		constexpr int F0Line0_ID = 0;

		// Line 1: F0Line1
		constexpr int F0Line1_TYPE = -1;
		constexpr int F0Line1_ID = 1;

		// StaticText 6: F0Statictext6
		constexpr int F0Statictext6_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F0Statictext6_ID = 6;

		// UserButton 0: F0UnitButton
		constexpr int F0UnitButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0UnitButton_ID = 0;

		// iLedDigits 7: F0YWorkDRO
		constexpr int F0YWorkDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0YWorkDRO_ID = 7;

		// UserImages 0: F0StatusImage
		constexpr int F0StatusImage_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F0StatusImage_ID = 0;

		// iLedDigits 8: F0YSafeDRO
		constexpr int F0YSafeDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F0YSafeDRO_ID = 8;

		// Image 1: F0Image1
		constexpr int F0Image1_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F0Image1_ID = 1;

		// Image 2: F0Image2
		constexpr int F0Image2_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F0Image2_ID = 2;

		// Image 3: F0Image3
		constexpr int F0Image3_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F0Image3_ID = 3;

		// Image 4: F0Image4
		constexpr int F0Image4_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F0Image4_ID = 4;

		// Image 5: F0Image5
		constexpr int F0Image5_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F0Image5_ID = 5;

		// Image 6: F0Image6
		constexpr int F0Image6_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F0Image6_ID = 6;

		// UserButton 1: F0ModeSetupButton
		constexpr int F0ModeSetupButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ModeSetupButton_ID = 1;

		// UserButton 2: F0ModeFlatButton
		constexpr int F0ModeFlatButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ModeFlatButton_ID = 2;

		// UserButton 3: F0ModeSideButton
		constexpr int F0ModeSideButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ModeSideButton_ID = 3;

		// UserButton 4: F0ModeCylButton
		constexpr int F0ModeCylButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ModeCylButton_ID = 4;

		// UserButton 5: F0ModeDressButton
		constexpr int F0ModeDressButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ModeDressButton_ID = 5;

		// UserButton 6: F0SettingsButton
		constexpr int F0SettingsButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0SettingsButton_ID = 6;

		// UserButton 7: F0XZeroButton
		constexpr int F0XZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0XZeroButton_ID = 7;

		// UserButton 8: F0YZeroButton
		constexpr int F0YZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0YZeroButton_ID = 8;

		// UserButton 9: F0ZZeroButton
		constexpr int F0ZZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ZZeroButton_ID = 9;

		// UserButton 10: F0XSetStartButton
		constexpr int F0XSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0XSetStartButton_ID = 10;

		// UserButton 11: F0ZSetStartButton
		constexpr int F0ZSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ZSetStartButton_ID = 11;

		// UserButton 12: F0YSetWorkButton
		constexpr int F0YSetWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0YSetWorkButton_ID = 12;

		// UserButton 13: F0XSetEndButton
		constexpr int F0XSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0XSetEndButton_ID = 13;

		// UserButton 14: F0ZSetEndButton
		constexpr int F0ZSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0ZSetEndButton_ID = 14;

		// UserButton 15: F0YSetSafeButton
		constexpr int F0YSetSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F0YSetSafeButton_ID = 15;

		// UserButton 16: GoUpButton
		constexpr int GoUpButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int GoUpButton_ID = 16;

		// UserButton 17: GoLeftButton
		constexpr int GoLeftButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int GoLeftButton_ID = 17;

		// UserButton 18: GoRightButton
		constexpr int GoRightButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int GoRightButton_ID = 18;

		// UserButton 19: GoDownButton
		constexpr int GoDownButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int GoDownButton_ID = 19;

		// UserImages 1: F0HomeIndicator
		constexpr int F0HomeIndicator_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F0HomeIndicator_ID = 1;

		// StaticText 4: Statictext4
		constexpr int Statictext4_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext4_ID = 4;

		// StaticText 7: Statictext7
		constexpr int Statictext7_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext7_ID = 7;

		// StaticText 8: Statictext8
		constexpr int Statictext8_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext8_ID = 8;

		// UserButton 20: GoSafeButton
		constexpr int GoSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int GoSafeButton_ID = 20;

		// UserButton 21: GoWorkButton
		constexpr int GoWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int GoWorkButton_ID = 21;

		// UserButton 22: CycleHomeButton
		constexpr int CycleHomeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int CycleHomeButton_ID = 22;

		// UserButton 23: CycleTouchButton
		constexpr int CycleTouchButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int CycleTouchButton_ID = 23;

		// Rectangle 0: Rectangle0
		constexpr int Rectangle0_TYPE = -1;
		constexpr int Rectangle0_ID = 0;

		// Strings 0: F0Message
		constexpr int F0Message_TYPE = GENIE_OBJ_STRINGS;
		constexpr int F0Message_ID = 0;

	}

	// Form 1: Splash
	namespace SPLASH {

		constexpr int FORM_ID = 1;

		// Image 0: Logo
		constexpr int Logo_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Logo_ID = 0;

		// StaticText 3: LoadingMessage
		constexpr int LoadingMessage_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int LoadingMessage_ID = 3;

	}

	// Form 2: InitMechanics
	namespace INITMECHANICS {

		constexpr int FORM_ID = 2;

		// Image 7: Image7
		constexpr int Image7_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image7_ID = 7;

		// StaticText 5: Statictext5
		constexpr int Statictext5_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext5_ID = 5;

	}

	// Form 3: FlatMode
	namespace FLATMODE {

		constexpr int FORM_ID = 3;

		// iLedDigits 9: F3XDro
		constexpr int F3XDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3XDro_ID = 9;

		// iLedDigits 10: F3YDro
		constexpr int F3YDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3YDro_ID = 10;

		// iLedDigits 11: F3ZDro
		constexpr int F3ZDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3ZDro_ID = 11;

		// iLed 8: F3XJog
		constexpr int F3XJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F3XJog_ID = 8;

		// iLed 9: F3YJog
		constexpr int F3YJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F3YJog_ID = 9;

		// iLed 10: F3ZJog
		constexpr int F3ZJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F3ZJog_ID = 10;

		// StaticText 9: F3XLabel
		constexpr int F3XLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F3XLabel_ID = 9;

		// StaticText 10: F3YLabel
		constexpr int F3YLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F3YLabel_ID = 10;

		// StaticText 11: F3ZLabel
		constexpr int F3ZLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F3ZLabel_ID = 11;

		// iLed 11: F3Resolution1
		constexpr int F3Resolution1_TYPE = GENIE_OBJ_ILED;
		constexpr int F3Resolution1_ID = 11;

		// iLed 12: F3Resolution10
		constexpr int F3Resolution10_TYPE = GENIE_OBJ_ILED;
		constexpr int F3Resolution10_ID = 12;

		// iLed 13: F3Resolution100
		constexpr int F3Resolution100_TYPE = GENIE_OBJ_ILED;
		constexpr int F3Resolution100_ID = 13;

		// iLed 14: F3Resolution1000
		constexpr int F3Resolution1000_TYPE = GENIE_OBJ_ILED;
		constexpr int F3Resolution1000_ID = 14;

		// iLed 15: F3Resolution10000
		constexpr int F3Resolution10000_TYPE = GENIE_OBJ_ILED;
		constexpr int F3Resolution10000_ID = 15;

		// iLedDigits 12: F3XStartDRO
		constexpr int F3XStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3XStartDRO_ID = 12;

		// iLedDigits 13: F3XEndDRO
		constexpr int F3XEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3XEndDRO_ID = 13;

		// iLedDigits 14: F3ZStartDRO
		constexpr int F3ZStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3ZStartDRO_ID = 14;

		// iLedDigits 15: F3ZEndDRO
		constexpr int F3ZEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3ZEndDRO_ID = 15;

		// Line 2: F3Line0
		constexpr int F3Line0_TYPE = -1;
		constexpr int F3Line0_ID = 2;

		// Line 3: F3Line1
		constexpr int F3Line1_TYPE = -1;
		constexpr int F3Line1_ID = 3;

		// UserButton 24: F3UnitButton
		constexpr int F3UnitButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3UnitButton_ID = 24;

		// iLedDigits 16: F3YWorkDRO
		constexpr int F3YWorkDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3YWorkDRO_ID = 16;

		// UserImages 2: F3StatusImage
		constexpr int F3StatusImage_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F3StatusImage_ID = 2;

		// iLedDigits 17: F3YSafeDRO
		constexpr int F3YSafeDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F3YSafeDRO_ID = 17;

		// Image 8: F3Image1
		constexpr int F3Image1_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F3Image1_ID = 8;

		// Image 9: F3Image2
		constexpr int F3Image2_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F3Image2_ID = 9;

		// Image 10: F3Image3
		constexpr int F3Image3_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F3Image3_ID = 10;

		// Image 11: F3Image4
		constexpr int F3Image4_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F3Image4_ID = 11;

		// Image 12: F3Image5
		constexpr int F3Image5_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F3Image5_ID = 12;

		// Image 13: F3Image6
		constexpr int F3Image6_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F3Image6_ID = 13;

		// UserButton 25: F3ModeSetupButton
		constexpr int F3ModeSetupButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ModeSetupButton_ID = 25;

		// UserButton 26: F3ModeFlatButton
		constexpr int F3ModeFlatButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ModeFlatButton_ID = 26;

		// UserButton 27: F3ModeSideButton
		constexpr int F3ModeSideButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ModeSideButton_ID = 27;

		// UserButton 28: F3ModeCylButton
		constexpr int F3ModeCylButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ModeCylButton_ID = 28;

		// UserButton 29: F3ModeDressButton
		constexpr int F3ModeDressButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ModeDressButton_ID = 29;

		// UserButton 30: F3SettingsButton
		constexpr int F3SettingsButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3SettingsButton_ID = 30;

		// UserButton 31: F3XZeroButton
		constexpr int F3XZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3XZeroButton_ID = 31;

		// UserButton 32: F3YZeroButton
		constexpr int F3YZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3YZeroButton_ID = 32;

		// UserButton 33: F3ZZeroButton
		constexpr int F3ZZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ZZeroButton_ID = 33;

		// UserButton 34: F3XSetStartButton
		constexpr int F3XSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3XSetStartButton_ID = 34;

		// UserButton 35: F3ZSetStartButton
		constexpr int F3ZSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ZSetStartButton_ID = 35;

		// UserButton 36: F3YSetWorkButton
		constexpr int F3YSetWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3YSetWorkButton_ID = 36;

		// UserButton 37: F3XSetEndButton
		constexpr int F3XSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3XSetEndButton_ID = 37;

		// UserButton 38: F3ZSetEndButton
		constexpr int F3ZSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3ZSetEndButton_ID = 38;

		// UserButton 39: F3YSetSafeButton
		constexpr int F3YSetSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F3YSetSafeButton_ID = 39;

		// UserImages 3: F3HomeIndicator
		constexpr int F3HomeIndicator_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F3HomeIndicator_ID = 3;

		// Strings 1: F3Message
		constexpr int F3Message_TYPE = GENIE_OBJ_STRINGS;
		constexpr int F3Message_ID = 1;

		// iLedDigits 45: RoughDepthDRO
		constexpr int RoughDepthDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int RoughDepthDRO_ID = 45;

		// StaticText 21: Statictext21
		constexpr int Statictext21_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext21_ID = 21;

		// Trackbar 0: RoughCountSlider
		constexpr int RoughCountSlider_TYPE = GENIE_OBJ_TRACKBAR;
		constexpr int RoughCountSlider_ID = 0;

		// iLedDigits 46: RoughCountDRO
		constexpr int RoughCountDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int RoughCountDRO_ID = 46;

		// StaticText 25: Statictext25
		constexpr int Statictext25_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext25_ID = 25;

		// Trackbar 1: RoughDepthSlider
		constexpr int RoughDepthSlider_TYPE = GENIE_OBJ_TRACKBAR;
		constexpr int RoughDepthSlider_ID = 1;

		// Trackbar 2: FinishDepthSlider
		constexpr int FinishDepthSlider_TYPE = GENIE_OBJ_TRACKBAR;
		constexpr int FinishDepthSlider_ID = 2;

		// StaticText 26: Statictext26
		constexpr int Statictext26_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext26_ID = 26;

		// iLedDigits 47: FinishDepthDRO
		constexpr int FinishDepthDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int FinishDepthDRO_ID = 47;

		// StaticText 27: Statictext27
		constexpr int Statictext27_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext27_ID = 27;

		// iLedDigits 48: FinishCountDRO
		constexpr int FinishCountDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int FinishCountDRO_ID = 48;

		// Trackbar 3: FinishCountSlider
		constexpr int FinishCountSlider_TYPE = GENIE_OBJ_TRACKBAR;
		constexpr int FinishCountSlider_ID = 3;

		// StaticText 28: Statictext28
		constexpr int Statictext28_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext28_ID = 28;

		// Trackbar 4: SparkCountSlider
		constexpr int SparkCountSlider_TYPE = GENIE_OBJ_TRACKBAR;
		constexpr int SparkCountSlider_ID = 4;

		// iLedDigits 49: SparkCountDRO
		constexpr int SparkCountDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int SparkCountDRO_ID = 49;

		// UserButton 88: RoughFeedButton
		constexpr int RoughFeedButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int RoughFeedButton_ID = 88;

		// UserButton 89: FinishFeedButton
		constexpr int FinishFeedButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int FinishFeedButton_ID = 89;

		// UserButton 90: AutoGrindButton
		constexpr int AutoGrindButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int AutoGrindButton_ID = 90;

	}

	// Form 4: SideMode
	namespace SIDEMODE {

		constexpr int FORM_ID = 4;

		// iLedDigits 18: F4XDro
		constexpr int F4XDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4XDro_ID = 18;

		// iLedDigits 19: F4YDro
		constexpr int F4YDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4YDro_ID = 19;

		// iLedDigits 20: F4ZDro
		constexpr int F4ZDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4ZDro_ID = 20;

		// iLed 16: F4XJog
		constexpr int F4XJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F4XJog_ID = 16;

		// iLed 17: F4YJog
		constexpr int F4YJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F4YJog_ID = 17;

		// iLed 18: F4ZJog
		constexpr int F4ZJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F4ZJog_ID = 18;

		// StaticText 12: F4XLabel
		constexpr int F4XLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F4XLabel_ID = 12;

		// StaticText 13: F4YLabel
		constexpr int F4YLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F4YLabel_ID = 13;

		// StaticText 14: F4ZLabel
		constexpr int F4ZLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F4ZLabel_ID = 14;

		// iLed 19: F4Resolution1
		constexpr int F4Resolution1_TYPE = GENIE_OBJ_ILED;
		constexpr int F4Resolution1_ID = 19;

		// iLed 20: F4Resolution10
		constexpr int F4Resolution10_TYPE = GENIE_OBJ_ILED;
		constexpr int F4Resolution10_ID = 20;

		// iLed 21: F4Resolution100
		constexpr int F4Resolution100_TYPE = GENIE_OBJ_ILED;
		constexpr int F4Resolution100_ID = 21;

		// iLed 22: F4Resolution1000
		constexpr int F4Resolution1000_TYPE = GENIE_OBJ_ILED;
		constexpr int F4Resolution1000_ID = 22;

		// iLed 23: F4Resolution10000
		constexpr int F4Resolution10000_TYPE = GENIE_OBJ_ILED;
		constexpr int F4Resolution10000_ID = 23;

		// iLedDigits 21: F4XStartDRO
		constexpr int F4XStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4XStartDRO_ID = 21;

		// iLedDigits 22: F4XEndDRO
		constexpr int F4XEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4XEndDRO_ID = 22;

		// iLedDigits 23: F4ZStartDRO
		constexpr int F4ZStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4ZStartDRO_ID = 23;

		// iLedDigits 24: F4ZEndDRO
		constexpr int F4ZEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4ZEndDRO_ID = 24;

		// Line 4: F4Line0
		constexpr int F4Line0_TYPE = -1;
		constexpr int F4Line0_ID = 4;

		// Line 5: F4Line1
		constexpr int F4Line1_TYPE = -1;
		constexpr int F4Line1_ID = 5;

		// UserButton 40: F4UnitButton
		constexpr int F4UnitButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4UnitButton_ID = 40;

		// iLedDigits 25: F4YWorkDRO
		constexpr int F4YWorkDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4YWorkDRO_ID = 25;

		// UserImages 4: F4StatusImage
		constexpr int F4StatusImage_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F4StatusImage_ID = 4;

		// iLedDigits 26: F4YSafeDRO
		constexpr int F4YSafeDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F4YSafeDRO_ID = 26;

		// Image 14: F4Image1
		constexpr int F4Image1_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F4Image1_ID = 14;

		// Image 15: F4Image2
		constexpr int F4Image2_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F4Image2_ID = 15;

		// Image 16: F4Image3
		constexpr int F4Image3_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F4Image3_ID = 16;

		// Image 17: F4Image4
		constexpr int F4Image4_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F4Image4_ID = 17;

		// Image 18: F4Image5
		constexpr int F4Image5_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F4Image5_ID = 18;

		// Image 19: F4Image6
		constexpr int F4Image6_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F4Image6_ID = 19;

		// UserButton 41: F4ModeSetupButton
		constexpr int F4ModeSetupButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ModeSetupButton_ID = 41;

		// UserButton 42: F4ModeFlatButton
		constexpr int F4ModeFlatButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ModeFlatButton_ID = 42;

		// UserButton 43: F4ModeSideButton
		constexpr int F4ModeSideButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ModeSideButton_ID = 43;

		// UserButton 44: F4ModeCylButton
		constexpr int F4ModeCylButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ModeCylButton_ID = 44;

		// UserButton 45: F4ModeDressButton
		constexpr int F4ModeDressButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ModeDressButton_ID = 45;

		// UserButton 46: F4SettingsButton
		constexpr int F4SettingsButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4SettingsButton_ID = 46;

		// UserButton 47: F4XZeroButton
		constexpr int F4XZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4XZeroButton_ID = 47;

		// UserButton 48: F4YZeroButton
		constexpr int F4YZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4YZeroButton_ID = 48;

		// UserButton 49: F4ZZeroButton
		constexpr int F4ZZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ZZeroButton_ID = 49;

		// UserButton 50: F4XSetStartButton
		constexpr int F4XSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4XSetStartButton_ID = 50;

		// UserButton 51: F4ZSetStartButton
		constexpr int F4ZSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ZSetStartButton_ID = 51;

		// UserButton 52: F4YSetWorkButton
		constexpr int F4YSetWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4YSetWorkButton_ID = 52;

		// UserButton 53: F4XSetEndButton
		constexpr int F4XSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4XSetEndButton_ID = 53;

		// UserButton 54: F4ZSetEndButton
		constexpr int F4ZSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4ZSetEndButton_ID = 54;

		// UserButton 55: F4YSetSafeButton
		constexpr int F4YSetSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F4YSetSafeButton_ID = 55;

		// UserImages 5: F4HomeIndicator
		constexpr int F4HomeIndicator_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F4HomeIndicator_ID = 5;

		// Strings 2: F4Message
		constexpr int F4Message_TYPE = GENIE_OBJ_STRINGS;
		constexpr int F4Message_ID = 2;

		// StaticText 22: Statictext22
		constexpr int Statictext22_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext22_ID = 22;

	}

	// Form 5: CylMode
	namespace CYLMODE {

		constexpr int FORM_ID = 5;

		// iLedDigits 27: F5XDro
		constexpr int F5XDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5XDro_ID = 27;

		// iLedDigits 28: F5YDro
		constexpr int F5YDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5YDro_ID = 28;

		// iLedDigits 29: F5ZDro
		constexpr int F5ZDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5ZDro_ID = 29;

		// iLed 24: F5XJog
		constexpr int F5XJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F5XJog_ID = 24;

		// iLed 25: F5YJog
		constexpr int F5YJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F5YJog_ID = 25;

		// iLed 26: F5ZJog
		constexpr int F5ZJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F5ZJog_ID = 26;

		// StaticText 15: F5XLabel
		constexpr int F5XLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F5XLabel_ID = 15;

		// StaticText 16: F5YLabel
		constexpr int F5YLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F5YLabel_ID = 16;

		// StaticText 17: F5ZLabel
		constexpr int F5ZLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F5ZLabel_ID = 17;

		// iLed 27: F5Resolution1
		constexpr int F5Resolution1_TYPE = GENIE_OBJ_ILED;
		constexpr int F5Resolution1_ID = 27;

		// iLed 28: F5Resolution10
		constexpr int F5Resolution10_TYPE = GENIE_OBJ_ILED;
		constexpr int F5Resolution10_ID = 28;

		// iLed 29: F5Resolution100
		constexpr int F5Resolution100_TYPE = GENIE_OBJ_ILED;
		constexpr int F5Resolution100_ID = 29;

		// iLed 30: F5Resolution1000
		constexpr int F5Resolution1000_TYPE = GENIE_OBJ_ILED;
		constexpr int F5Resolution1000_ID = 30;

		// iLed 31: F5Resolution10000
		constexpr int F5Resolution10000_TYPE = GENIE_OBJ_ILED;
		constexpr int F5Resolution10000_ID = 31;

		// iLedDigits 30: F5XStartDRO
		constexpr int F5XStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5XStartDRO_ID = 30;

		// iLedDigits 31: F5XEndDRO
		constexpr int F5XEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5XEndDRO_ID = 31;

		// iLedDigits 32: F5ZStartDRO
		constexpr int F5ZStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5ZStartDRO_ID = 32;

		// iLedDigits 33: F5ZEndDRO
		constexpr int F5ZEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5ZEndDRO_ID = 33;

		// Line 6: F5Line0
		constexpr int F5Line0_TYPE = -1;
		constexpr int F5Line0_ID = 6;

		// Line 7: F5Line1
		constexpr int F5Line1_TYPE = -1;
		constexpr int F5Line1_ID = 7;

		// UserButton 56: F5UnitButton
		constexpr int F5UnitButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5UnitButton_ID = 56;

		// iLedDigits 34: F5YWorkDRO
		constexpr int F5YWorkDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5YWorkDRO_ID = 34;

		// UserImages 6: F5StatusImage
		constexpr int F5StatusImage_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F5StatusImage_ID = 6;

		// iLedDigits 35: F5YSafeDRO
		constexpr int F5YSafeDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F5YSafeDRO_ID = 35;

		// Image 20: F5Image1
		constexpr int F5Image1_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F5Image1_ID = 20;

		// Image 21: F5Image2
		constexpr int F5Image2_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F5Image2_ID = 21;

		// Image 22: F5Image3
		constexpr int F5Image3_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F5Image3_ID = 22;

		// Image 23: F5Image4
		constexpr int F5Image4_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F5Image4_ID = 23;

		// Image 24: F5Image5
		constexpr int F5Image5_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F5Image5_ID = 24;

		// Image 25: F5Image6
		constexpr int F5Image6_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F5Image6_ID = 25;

		// UserButton 57: F5ModeSetupButton
		constexpr int F5ModeSetupButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ModeSetupButton_ID = 57;

		// UserButton 58: F5ModeFlatButton
		constexpr int F5ModeFlatButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ModeFlatButton_ID = 58;

		// UserButton 59: F5ModeSideButton
		constexpr int F5ModeSideButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ModeSideButton_ID = 59;

		// UserButton 60: F5ModeCylButton
		constexpr int F5ModeCylButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ModeCylButton_ID = 60;

		// UserButton 61: F5ModeDressButton
		constexpr int F5ModeDressButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ModeDressButton_ID = 61;

		// UserButton 62: F5SettingsButton
		constexpr int F5SettingsButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5SettingsButton_ID = 62;

		// UserButton 63: F5XZeroButton
		constexpr int F5XZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5XZeroButton_ID = 63;

		// UserButton 64: F5YZeroButton
		constexpr int F5YZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5YZeroButton_ID = 64;

		// UserButton 65: F5ZZeroButton
		constexpr int F5ZZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ZZeroButton_ID = 65;

		// UserButton 66: F5XSetStartButton
		constexpr int F5XSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5XSetStartButton_ID = 66;

		// UserButton 67: F5ZSetStartButton
		constexpr int F5ZSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ZSetStartButton_ID = 67;

		// UserButton 68: F5YSetWorkButton
		constexpr int F5YSetWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5YSetWorkButton_ID = 68;

		// UserButton 69: F5XSetEndButton
		constexpr int F5XSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5XSetEndButton_ID = 69;

		// UserButton 70: F5ZSetEndButton
		constexpr int F5ZSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5ZSetEndButton_ID = 70;

		// UserButton 71: F5YSetSafeButton
		constexpr int F5YSetSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F5YSetSafeButton_ID = 71;

		// UserImages 7: F5HomeIndicator
		constexpr int F5HomeIndicator_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F5HomeIndicator_ID = 7;

		// Strings 3: F5Message
		constexpr int F5Message_TYPE = GENIE_OBJ_STRINGS;
		constexpr int F5Message_ID = 3;

		// StaticText 23: Statictext23
		constexpr int Statictext23_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext23_ID = 23;

	}

	// Form 6: DressMode
	namespace DRESSMODE {

		constexpr int FORM_ID = 6;

		// iLedDigits 36: F6XDro
		constexpr int F6XDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6XDro_ID = 36;

		// iLedDigits 37: F6YDro
		constexpr int F6YDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6YDro_ID = 37;

		// iLedDigits 38: F6ZDro
		constexpr int F6ZDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6ZDro_ID = 38;

		// iLed 32: F6XJog
		constexpr int F6XJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F6XJog_ID = 32;

		// iLed 33: F6YJog
		constexpr int F6YJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F6YJog_ID = 33;

		// iLed 34: F6ZJog
		constexpr int F6ZJog_TYPE = GENIE_OBJ_ILED;
		constexpr int F6ZJog_ID = 34;

		// StaticText 18: F6XLabel
		constexpr int F6XLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F6XLabel_ID = 18;

		// StaticText 19: F6YLabel
		constexpr int F6YLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F6YLabel_ID = 19;

		// StaticText 20: F6ZLabel
		constexpr int F6ZLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int F6ZLabel_ID = 20;

		// iLed 35: F6Resolution1
		constexpr int F6Resolution1_TYPE = GENIE_OBJ_ILED;
		constexpr int F6Resolution1_ID = 35;

		// iLed 36: F6Resolution10
		constexpr int F6Resolution10_TYPE = GENIE_OBJ_ILED;
		constexpr int F6Resolution10_ID = 36;

		// iLed 37: F6Resolution100
		constexpr int F6Resolution100_TYPE = GENIE_OBJ_ILED;
		constexpr int F6Resolution100_ID = 37;

		// iLed 38: F6Resolution1000
		constexpr int F6Resolution1000_TYPE = GENIE_OBJ_ILED;
		constexpr int F6Resolution1000_ID = 38;

		// iLed 39: F6Resolution10000
		constexpr int F6Resolution10000_TYPE = GENIE_OBJ_ILED;
		constexpr int F6Resolution10000_ID = 39;

		// iLedDigits 39: F6XStartDRO
		constexpr int F6XStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6XStartDRO_ID = 39;

		// iLedDigits 40: F6XEndDRO
		constexpr int F6XEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6XEndDRO_ID = 40;

		// iLedDigits 41: F6ZStartDRO
		constexpr int F6ZStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6ZStartDRO_ID = 41;

		// iLedDigits 42: F6ZEndDRO
		constexpr int F6ZEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6ZEndDRO_ID = 42;

		// Line 8: F6Line0
		constexpr int F6Line0_TYPE = -1;
		constexpr int F6Line0_ID = 8;

		// Line 9: F6Line1
		constexpr int F6Line1_TYPE = -1;
		constexpr int F6Line1_ID = 9;

		// UserButton 72: F6UnitButton
		constexpr int F6UnitButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6UnitButton_ID = 72;

		// iLedDigits 43: F6YWorkDRO
		constexpr int F6YWorkDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6YWorkDRO_ID = 43;

		// UserImages 8: F6StatusImage
		constexpr int F6StatusImage_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F6StatusImage_ID = 8;

		// iLedDigits 44: F6YSafeDRO
		constexpr int F6YSafeDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int F6YSafeDRO_ID = 44;

		// Image 26: F6Image1
		constexpr int F6Image1_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F6Image1_ID = 26;

		// Image 27: F6Image2
		constexpr int F6Image2_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F6Image2_ID = 27;

		// Image 28: F6Image3
		constexpr int F6Image3_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F6Image3_ID = 28;

		// Image 29: F6Image4
		constexpr int F6Image4_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F6Image4_ID = 29;

		// Image 30: F6Image5
		constexpr int F6Image5_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F6Image5_ID = 30;

		// Image 31: F6Image6
		constexpr int F6Image6_TYPE = GENIE_OBJ_IMAGE;
		constexpr int F6Image6_ID = 31;

		// UserButton 73: F6ModeSetupButton
		constexpr int F6ModeSetupButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ModeSetupButton_ID = 73;

		// UserButton 74: F6ModeFlatButton
		constexpr int F6ModeFlatButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ModeFlatButton_ID = 74;

		// UserButton 75: F6ModeSideButton
		constexpr int F6ModeSideButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ModeSideButton_ID = 75;

		// UserButton 76: F6ModeCylButton
		constexpr int F6ModeCylButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ModeCylButton_ID = 76;

		// UserButton 77: F6ModeDressButton
		constexpr int F6ModeDressButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ModeDressButton_ID = 77;

		// UserButton 78: F6SettingsButton
		constexpr int F6SettingsButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6SettingsButton_ID = 78;

		// UserButton 79: F6XZeroButton
		constexpr int F6XZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6XZeroButton_ID = 79;

		// UserButton 80: F6YZeroButton
		constexpr int F6YZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6YZeroButton_ID = 80;

		// UserButton 81: F6ZZeroButton
		constexpr int F6ZZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ZZeroButton_ID = 81;

		// UserButton 82: F6XSetStartButton
		constexpr int F6XSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6XSetStartButton_ID = 82;

		// UserButton 83: F6ZSetStartButton
		constexpr int F6ZSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ZSetStartButton_ID = 83;

		// UserButton 84: F6YSetWorkButton
		constexpr int F6YSetWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6YSetWorkButton_ID = 84;

		// UserButton 85: F6XSetEndButton
		constexpr int F6XSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6XSetEndButton_ID = 85;

		// UserButton 86: F6ZSetEndButton
		constexpr int F6ZSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6ZSetEndButton_ID = 86;

		// UserButton 87: F6YSetSafeButton
		constexpr int F6YSetSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int F6YSetSafeButton_ID = 87;

		// UserImages 9: F6HomeIndicator
		constexpr int F6HomeIndicator_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int F6HomeIndicator_ID = 9;

		// Strings 4: F6Message
		constexpr int F6Message_TYPE = GENIE_OBJ_STRINGS;
		constexpr int F6Message_ID = 4;

		// StaticText 24: Statictext24
		constexpr int Statictext24_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext24_ID = 24;

	}

}

#endif // HMI_CONSTANTS_H

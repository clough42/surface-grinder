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

#ifndef HMI_CONSTANTS_H
#define HMI_CONSTANTS_H

#include <genieArduinoDEV.h>

namespace HMI {

    constexpr int UNITS_BUTTON_VAL_INCH = 0;
    constexpr int UNITS_BUTTON_VAL_MM = 1;

	// Form 0: SetupMode
	namespace SETUPMODE {

		constexpr int FORM_ID = 0;

		// iLedDigits 0: XDro
		constexpr int XDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int XDro_ID = 0;

		// iLedDigits 1: YDro
		constexpr int YDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int YDro_ID = 1;

		// iLedDigits 2: ZDro
		constexpr int ZDro_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int ZDro_ID = 2;

		// iLed 0: XJog
		constexpr int XJog_TYPE = GENIE_OBJ_ILED;
		constexpr int XJog_ID = 0;

		// iLed 1: YJog
		constexpr int YJog_TYPE = GENIE_OBJ_ILED;
		constexpr int YJog_ID = 1;

		// iLed 2: ZJog
		constexpr int ZJog_TYPE = GENIE_OBJ_ILED;
		constexpr int ZJog_ID = 2;

		// StaticText 0: XLabel
		constexpr int XLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int XLabel_ID = 0;

		// StaticText 1: YLabel
		constexpr int YLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int YLabel_ID = 1;

		// StaticText 2: ZLabel
		constexpr int ZLabel_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int ZLabel_ID = 2;

		// iLed 3: Resolution1
		constexpr int Resolution1_TYPE = GENIE_OBJ_ILED;
		constexpr int Resolution1_ID = 3;

		// iLed 4: Resolution10
		constexpr int Resolution10_TYPE = GENIE_OBJ_ILED;
		constexpr int Resolution10_ID = 4;

		// iLed 5: Resolution100
		constexpr int Resolution100_TYPE = GENIE_OBJ_ILED;
		constexpr int Resolution100_ID = 5;

		// iLed 6: Resolution1000
		constexpr int Resolution1000_TYPE = GENIE_OBJ_ILED;
		constexpr int Resolution1000_ID = 6;

		// iLed 7: Resolution10000
		constexpr int Resolution10000_TYPE = GENIE_OBJ_ILED;
		constexpr int Resolution10000_ID = 7;

		// iLedDigits 3: XStartDRO
		constexpr int XStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int XStartDRO_ID = 3;

		// iLedDigits 4: XEndDRO
		constexpr int XEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int XEndDRO_ID = 4;

		// iLedDigits 5: ZStartDRO
		constexpr int ZStartDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int ZStartDRO_ID = 5;

		// iLedDigits 6: ZEndDRO
		constexpr int ZEndDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int ZEndDRO_ID = 6;

		// Line 0: Line0
		constexpr int Line0_TYPE = -1;
		constexpr int Line0_ID = 0;

		// Line 1: Line1
		constexpr int Line1_TYPE = -1;
		constexpr int Line1_ID = 1;

		// StaticText 6: Statictext6
		constexpr int Statictext6_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext6_ID = 6;

		// UserButton 0: UnitButton
		constexpr int UnitButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int UnitButton_ID = 0;

		// iLedDigits 7: YWorkDRO
		constexpr int YWorkDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int YWorkDRO_ID = 7;

		// UserImages 0: StatusImage
		constexpr int StatusImage_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int StatusImage_ID = 0;

		// iLedDigits 8: YSafeDRO
		constexpr int YSafeDRO_TYPE = GENIE_OBJ_ILED_DIGITS;
		constexpr int YSafeDRO_ID = 8;

		// Image 1: Image1
		constexpr int Image1_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image1_ID = 1;

		// Image 2: Image2
		constexpr int Image2_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image2_ID = 2;

		// Image 3: Image3
		constexpr int Image3_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image3_ID = 3;

		// Image 4: Image4
		constexpr int Image4_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image4_ID = 4;

		// Image 5: Image5
		constexpr int Image5_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image5_ID = 5;

		// Image 6: Image6
		constexpr int Image6_TYPE = GENIE_OBJ_IMAGE;
		constexpr int Image6_ID = 6;

		// UserButton 1: ModeSetupButton
		constexpr int ModeSetupButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ModeSetupButton_ID = 1;

		// UserButton 2: ModeFlatButton
		constexpr int ModeFlatButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ModeFlatButton_ID = 2;

		// UserButton 3: ModeSideButton
		constexpr int ModeSideButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ModeSideButton_ID = 3;

		// UserButton 4: ModeCylButton
		constexpr int ModeCylButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ModeCylButton_ID = 4;

		// UserButton 5: ModeDressButton
		constexpr int ModeDressButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ModeDressButton_ID = 5;

		// UserButton 6: SettingsButton
		constexpr int SettingsButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int SettingsButton_ID = 6;

		// UserButton 7: XZeroButton
		constexpr int XZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int XZeroButton_ID = 7;

		// UserButton 8: YZeroButton
		constexpr int YZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int YZeroButton_ID = 8;

		// UserButton 9: ZZeroButton
		constexpr int ZZeroButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ZZeroButton_ID = 9;

		// UserButton 10: XSetStartButton
		constexpr int XSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int XSetStartButton_ID = 10;

		// UserButton 11: ZSetStartButton
		constexpr int ZSetStartButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ZSetStartButton_ID = 11;

		// UserButton 12: YSetWorkButton
		constexpr int YSetWorkButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int YSetWorkButton_ID = 12;

		// UserButton 13: XSetEndButton
		constexpr int XSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int XSetEndButton_ID = 13;

		// UserButton 14: ZSetEndButton
		constexpr int ZSetEndButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int ZSetEndButton_ID = 14;

		// UserButton 15: YSetSafeButton
		constexpr int YSetSafeButton_TYPE = GENIE_OBJ_USERBUTTON;
		constexpr int YSetSafeButton_ID = 15;

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

		// UserImages 1: HomeIndicator
		constexpr int HomeIndicator_TYPE = GENIE_OBJ_USERIMAGES;
		constexpr int HomeIndicator_ID = 1;

		// StaticText 4: Statictext4
		constexpr int Statictext4_TYPE = GENIE_OBJ_STATIC_TEXT;
		constexpr int Statictext4_ID = 4;

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

}

#endif // HMI_CONSTANTS_H

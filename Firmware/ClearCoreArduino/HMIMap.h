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

#ifndef HMI_MAP_H
#define HMI_MAP_H

#include "HMIConstants.h"

namespace HMI {

	namespace ALLMODES {

		using namespace HMI::SETUPMODE;
		using namespace HMI::FLATMODE;
		using namespace HMI::SIDEMODE;
		using namespace HMI::CYLMODE;
		using namespace HMI::DRESSMODE;

		constexpr int XDro_ID[] = { F0XDro_ID, 0, 0, F3XDro_ID, F4XDro_ID, F5XDro_ID, F6XDro_ID };
		constexpr int YDro_ID[] = { F0YDro_ID, 0, 0, F3YDro_ID, F4YDro_ID, F5YDro_ID, F6YDro_ID };
		constexpr int ZDro_ID[] = { F0ZDro_ID, 0, 0, F3ZDro_ID, F4ZDro_ID, F5ZDro_ID, F6ZDro_ID };

		constexpr int XJog_ID[] = { F0XJog_ID, 0, 0, F3XJog_ID, F4XJog_ID, F5XJog_ID, F6XJog_ID };
		constexpr int YJog_ID[] = { F0YJog_ID, 0, 0, F3YJog_ID, F4YJog_ID, F5YJog_ID, F6YJog_ID };
		constexpr int ZJog_ID[] = { F0ZJog_ID, 0, 0, F3ZJog_ID, F4ZJog_ID, F5ZJog_ID, F6ZJog_ID };

		constexpr int Resolution1_ID[] = { F0Resolution1_ID, 0, 0, F3Resolution1_ID, F4Resolution1_ID, F5Resolution1_ID, F6Resolution1_ID };
		constexpr int Resolution10_ID[] = { F0Resolution10_ID, 0, 0, F3Resolution10_ID, F4Resolution10_ID, F5Resolution10_ID, F6Resolution10_ID };
		constexpr int Resolution100_ID[] = { F0Resolution100_ID, 0, 0, F3Resolution100_ID, F4Resolution100_ID, F5Resolution100_ID, F6Resolution100_ID };
		constexpr int Resolution1000_ID[] = { F0Resolution1000_ID, 0, 0, F3Resolution1000_ID, F4Resolution1000_ID, F5Resolution1000_ID, F6Resolution1000_ID };
		constexpr int Resolution10000_ID[] = { F0Resolution10000_ID, 0, 0, F3Resolution10000_ID, F4Resolution10000_ID, F5Resolution10000_ID, F6Resolution10000_ID };

		constexpr int XStartDRO_ID[] = { F0XStartDRO_ID, 0, 0, F3XStartDRO_ID, F4XStartDRO_ID, F5XStartDRO_ID, F6XStartDRO_ID };
		constexpr int XEndDRO_ID[] = { F0XEndDRO_ID, 0, 0, F3XEndDRO_ID, F4XEndDRO_ID, F5XEndDRO_ID, F6XEndDRO_ID };
		constexpr int YWorkDRO_ID[] = { F0YWorkDRO_ID, 0, 0, F3YWorkDRO_ID, F4YWorkDRO_ID, F5YWorkDRO_ID, F6YWorkDRO_ID };
		constexpr int YSafeDRO_ID[] = { F0YSafeDRO_ID, 0, 0, F3YSafeDRO_ID, F4YSafeDRO_ID, F5YSafeDRO_ID, F6YSafeDRO_ID };
		constexpr int ZStartDRO_ID[] = { F0ZStartDRO_ID, 0, 0, F3ZStartDRO_ID, F4ZStartDRO_ID, F5ZStartDRO_ID, F6ZStartDRO_ID };
		constexpr int ZEndDRO_ID[] = { F0ZEndDRO_ID, 0, 0, F3ZEndDRO_ID, F4ZEndDRO_ID, F5ZEndDRO_ID, F6ZEndDRO_ID };

		constexpr int UnitButton_ID[] = { F0UnitButton_ID, 0, 0, F3UnitButton_ID, F4UnitButton_ID, F5UnitButton_ID, F6UnitButton_ID };
		constexpr int StatusImage_ID[] = { F0StatusImage_ID, 0, 0, F3StatusImage_ID, F4StatusImage_ID, F5StatusImage_ID, F6StatusImage_ID };

		constexpr int ModeSetupButton_ID[] = { F0ModeSetupButton_ID, 0, 0, F3ModeSetupButton_ID, F4ModeSetupButton_ID, F5ModeSetupButton_ID, F6ModeSetupButton_ID };
		constexpr int ModeFlatButton_ID[] = { F0ModeFlatButton_ID, 0, 0, F3ModeFlatButton_ID, F4ModeFlatButton_ID, F5ModeFlatButton_ID, F6ModeFlatButton_ID };
		constexpr int ModeSideButton_ID[] = { F0ModeSideButton_ID, 0, 0, F3ModeSideButton_ID, F4ModeSideButton_ID, F5ModeSideButton_ID, F6ModeSideButton_ID };
		constexpr int ModeCylButton_ID[] = { F0ModeCylButton_ID, 0, 0, F3ModeCylButton_ID, F4ModeCylButton_ID, F5ModeCylButton_ID, F6ModeCylButton_ID };
		constexpr int ModeDressButton_ID[] = { F0ModeDressButton_ID, 0, 0, F3ModeDressButton_ID, F4ModeDressButton_ID, F5ModeDressButton_ID, F6ModeDressButton_ID };

		constexpr int SettingsButton_ID[] = { F0SettingsButton_ID, 0, 0, F3SettingsButton_ID, F4SettingsButton_ID, F5SettingsButton_ID, F6SettingsButton_ID };

		constexpr int XZeroButton_ID[] = { F0XZeroButton_ID, 0, 0, F3XZeroButton_ID, F4XZeroButton_ID, F5XZeroButton_ID, F6XZeroButton_ID };
		constexpr int YZeroButton_ID[] = { F0YZeroButton_ID, 0, 0, F3YZeroButton_ID, F4YZeroButton_ID, F5YZeroButton_ID, F6YZeroButton_ID };
		constexpr int ZZeroButton_ID[] = { F0ZZeroButton_ID, 0, 0, F3ZZeroButton_ID, F4ZZeroButton_ID, F5ZZeroButton_ID, F6ZZeroButton_ID };

		constexpr int XSetStartButton_ID[] = { F0XSetStartButton_ID, 0, 0, F3XSetStartButton_ID, F4XSetStartButton_ID, F5XSetStartButton_ID, F6XSetStartButton_ID };
		constexpr int XSetEndButton_ID[] = { F0XSetEndButton_ID, 0, 0, F3XSetEndButton_ID, F4XSetEndButton_ID, F5XSetEndButton_ID, F6XSetEndButton_ID };
		constexpr int YSetWorkButton_ID[] = { F0YSetWorkButton_ID, 0, 0, F3YSetWorkButton_ID, F4YSetWorkButton_ID, F5YSetWorkButton_ID, F6YSetWorkButton_ID };
		constexpr int YSetSafeButton_ID[] = { F0YSetSafeButton_ID, 0, 0, F3YSetSafeButton_ID, F4YSetSafeButton_ID, F5YSetSafeButton_ID, F6YSetSafeButton_ID };
		constexpr int ZSetStartButton_ID[] = { F0ZSetStartButton_ID, 0, 0, F3ZSetStartButton_ID, F4ZSetStartButton_ID, F5ZSetStartButton_ID, F6ZSetStartButton_ID };
		constexpr int ZSetEndButton_ID[] = { F0ZSetEndButton_ID, 0, 0, F3ZSetEndButton_ID, F4ZSetEndButton_ID, F5ZSetEndButton_ID, F6ZSetEndButton_ID };

		constexpr int HomeIndicator_ID[] = { F0HomeIndicator_ID, 0, 0, F3HomeIndicator_ID, F4HomeIndicator_ID, F5HomeIndicator_ID, F6HomeIndicator_ID };

		constexpr int Message_ID[] = { F0Message_ID, 0, 0, F3Message_ID, F4Message_ID, F5Message_ID, F6Message_ID };
	}
}


#endif // HMI_MAP_H
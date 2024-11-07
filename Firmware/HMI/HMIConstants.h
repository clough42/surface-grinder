#ifndef HMI_CONSTANTS_H
#define HMI_CONSTANTS_H

namespace HMI {

	namespace FORM0 {

		// iLedDigits
		constexpr int XDRO = 0;
		// iLedDigits
		constexpr int YDRO = 1;
		// iLedDigits
		constexpr int ZDRO = 2;
		// WinButton
		constexpr int XZERO = 0;
		// WinButton
		constexpr int YZERO = 1;
		// WinButton
		constexpr int ZZERO = 2;
		// iLed
		constexpr int XJOG = 0;
		// iLed
		constexpr int YJOG = 1;
		// iLed
		constexpr int ZJOG = 2;
		// StaticText
		constexpr int XLABEL = 0;
		// StaticText
		constexpr int YLABEL = 1;
		// StaticText
		constexpr int ZLABEL = 2;
		// iLed
		constexpr int RESOLUTION1 = 3;
		// iLed
		constexpr int RESOLUTION10 = 4;
		// iLed
		constexpr int RESOLUTION100 = 5;
		// iLed
		constexpr int RESOLUTION1000 = 6;
		// iLed
		constexpr int RESOLUTION10000 = 7;
		// WinButton
		constexpr int XSTART = 4;
		// WinButton
		constexpr int XEND = 5;
		// iLedDigits
		constexpr int XSTARTDRO = 3;
		// iLedDigits
		constexpr int XENDDRO = 4;
		// WinButton
		constexpr int ZSTART = 6;
		// WinButton
		constexpr int ZEND = 7;
		// iLedDigits
		constexpr int ZSTARTDRO = 5;
		// iLedDigits
		constexpr int ZENDDRO = 6;
		// Line
		constexpr int LINE0 = 0;
		// Line
		constexpr int LINE1 = 1;
		// WinButton
		constexpr int TRAVERSELEFTBUTTON = 13;
		// WinButton
		constexpr int TRAVERSERIGHTBUTTON = 14;
		// WinButton
		constexpr int TRAVERSEUPBUTTON = 15;
		// WinButton
		constexpr int TRAVERSEDOWNBUTTON = 16;
		// StaticText
		constexpr int STATICTEXT6 = 6;
		// UserButton
		constexpr int UNITBUTTON = 0;
		// WinButton
		constexpr int YSAFE = 17;
		// iLedDigits
		constexpr int YWORKDRO = 7;
		// UserImages
		constexpr int USERIMAGES0 = 0;
		// WinButton
		constexpr int YWORK = 18;
		// iLedDigits
		constexpr int YSAFEDRO = 8;
		// Image
		constexpr int IMAGE1 = 1;
		// Image
		constexpr int IMAGE2 = 2;
		// Image
		constexpr int IMAGE3 = 3;
		// Image
		constexpr int IMAGE4 = 4;
		// Image
		constexpr int IMAGE5 = 5;
		// Image
		constexpr int IMAGE6 = 6;
		// UserButton
		constexpr int MODESETUPBUTTON = 1;
		// UserButton
		constexpr int MODEFLATBUTTON = 2;
		// UserButton
		constexpr int MODESIDEBUTTON = 3;
		// UserButton
		constexpr int MODECYLBYTTON = 4;
		// UserButton
		constexpr int MODEDRESSBUTTON = 5;
		// UserButton
		constexpr int SETTINGSBUTTON = 6;
	}

	namespace FORM1 {

		// Image
		constexpr int LOGO = 0;
		// StaticText
		constexpr int LOADINGMESSAGE = 3;
	}

}
#endif // HMI_CONSTANTS_H

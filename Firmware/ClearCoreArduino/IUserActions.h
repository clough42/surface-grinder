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

#ifndef I_USER_ACTIONS_H
#define I_USER_ACTIONS_H

#include "CommonEnums.h"

// Controller Interface for the View
//
// This interface defines the methods that the view can call on the controller.
// These are separated out into a separate interface to make it harder for
// the view to accidentally call methods that it shouldn't.
class IUserActions {
public:
    virtual ~IUserActions() = default;
    virtual void EnterEstop() = 0; 
    virtual void ClearEstop() = 0;
	virtual void CycleStart() = 0;
	virtual void CycleStop() = 0;
	virtual void SelectUnits(Units units) = 0;
	virtual void SelectAxis(Axis selectedAxis, int resolutionSwitchPosition) = 0;
    virtual void Jog(int32_t clicks) = 0;
	virtual void SetWorkOffset(Axis selectedAxis) = 0;
	virtual void SetStartLimit(Axis axis) = 0;
	virtual void SetEndLimit(Axis axis) = 0;
	virtual void SetOperatingMode(Mode mode) = 0;
};

#endif // I_USER_ACTIONS_H


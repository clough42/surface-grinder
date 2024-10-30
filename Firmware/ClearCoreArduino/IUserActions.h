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


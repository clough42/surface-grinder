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

#ifndef GRINDER_MODEL_H
#define GRINDER_MODEL_H

#include "MachineAxis.h"

class GrinderModel {
public:
    // Constructor that takes an array of three MachineAxis objects
    GrinderModel(MachineAxis* axes[3], DigitalInOut& leftLimit,	DigitalInOut& rightLimit);

    // Method to initialize all axes
    void Init();

    // Method to update all axes
    void Update();

    int32_t GetCurrentPositionNm(Axis axis) const {
		return m_axes[static_cast<int>(axis)]->GetCurrentPositionNm();
	};

	void JogAxisNm(Axis axis, int32_t distanceInNanometers) {
		m_axes[static_cast<int>(axis)]->JogNm(distanceInNanometers);
	}

	void ResetAndEnable() {
		for (int i = 0; i < 3; ++i) {
			m_axes[i]->ResetAndEnable();
		}
	}

private:
    MachineAxis* m_axes[3];
	DigitalInOut& m_leftLimit;
	DigitalInOut& m_rightLimit;
};

#endif // GRINDER_MODEL_H

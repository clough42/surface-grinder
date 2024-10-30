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

#ifndef GRINDERCONTROLLER_H
#define GRINDERCONTROLLER_H

#include "GrinderModel.h"
#include "GrinderView.h"
#include "IUserActions.h"

class GrinderController : public IUserActions {
public:
    GrinderController(GrinderModel& model, GrinderView& view)
        : m_model(model), m_view(view)
    {}

    void Init();
    void Update();

    void EnterEstop() override;
    void ClearEstop() override;
	void CycleStart() override;
	void CycleStop() override;
	void SelectUnits(Units units) override;
	void SelectAxis(Axis axisSwitchPosition, int resolutionSwitchPosition) override;
	void Jog(int32_t clicks) override;
	void SetWorkOffset(Axis selectedAxis) override;
	void SetStartLimit(Axis axis) override;
	void SetEndLimit(Axis axis) override;
	void SetOperatingMode(Mode mode) override;

private:
    void UpdateDROs();
	void UpdateDRO(Axis axis);
    void UpdateResolutionAndAxisIndicators();
    void UpdateLimitDros();

    int32_t ConvertToNm(int32_t units); // convert from (units * 2^5)
	int32_t ConvertToUnits(int32_t nanometers); // convert to (units * 2^5)

    GrinderModel& m_model;
    GrinderView& m_view;

    Units m_units = Units::INCHES;
	Mode m_mode = Mode::SETUP;
	Axis m_selectedAxis;
    int m_resolutionSwitchPosition = 0;
    int32_t m_selectedResolution;
    int32_t m_droWorkOffsets[3] = { 0, 0, 0 };
    int32_t m_startLimits[3] = { 0, 0, 0 };
    int32_t m_endLimits[3] = { 0, 0, 0 };
    
};

#endif // GRINDERCONTROLLER_H

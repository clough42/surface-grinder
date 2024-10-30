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

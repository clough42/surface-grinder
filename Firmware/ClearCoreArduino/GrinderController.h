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

#ifndef GRINDERCONTROLLER_H
#define GRINDERCONTROLLER_H

#include "Configuration.h"
#include "GrinderModel.h"
#include "GrinderView.h"
#include "IUserActions.h"
#include "Optional.h"
#include "TrackedValue.h"

class GrinderController : public IUserActions {
public:
    GrinderController(GrinderModel& model, GrinderView& view, Configuration& config)
		: m_model(model), m_view(view), m_config(config), m_mode(Mode::INIT), m_status(Status::IDLE), m_cycleType(CycleType::HOME), m_isHomed(false)
    {}

    void Init();
    void Update();

    void EnterEstop() override;
    void ClearEstop() override;
	void CycleStart() override;
	void CycleStop() override;
	void SelectUnits(Units units) override;
	void SelectAxis(Optional<Axis> axisSwitchPosition, Optional<int> resolutionSwitchPosition) override;
	void Jog(int32_t clicks) override;
	void SetWorkOffset(Axis selectedAxis) override;
	void SetStartLimit(Axis axis) override;
	void SetEndLimit(Axis axis) override;
    void SetSafePosition(Axis axis) override;
    void SetWorkPosition(Axis axis) override;
	void SetOperatingMode(Mode mode) override;
    void SetCycleType(CycleType cycleType) override;
	void TraverseToStartPosition(Axis axis) override;
	void TraverseToEndPosition(Axis axis) override;
	void TraverseToSafePosition(Axis axis) override;
	void TraverseToWorkPosition(Axis axis) override;    

private:
    void UpdateDROs();
	void UpdateDRO(Axis axis);
    void UpdateHomed();
    void UpdateResolutionAndAxisIndicators();
    void UpdateLimitDros();
    void UpdateError();

    int32_t ConvertToNm(int32_t units); // convert from (units * 2^5)
	int32_t ConvertToUnits(int32_t nanometers); // convert to (units * 2^5)

    GrinderModel& m_model;
    GrinderView& m_view;

    Units m_units = Units::INCHES;
    TrackedValue<Mode> m_mode;
	TrackedValue<Status> m_status;
    TrackedValue<CycleType> m_cycleType;
	TrackedValue<bool> m_isHomed;
	Optional<Axis> m_selectedAxis;
    Optional<int> m_resolutionSwitchPosition = 0;
    int32_t m_selectedResolution;
    Configuration& m_config;
    
};

#endif // GRINDERCONTROLLER_H

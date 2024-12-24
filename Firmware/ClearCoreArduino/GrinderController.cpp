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

#include "GrinderController.h"

void GrinderController::Init() {
	// Initialize the view
	m_view.Init(this);

	// Initialize the model
	m_model.Init();

	SetOperatingMode(Mode::SETUP);
}

void GrinderController::Update() {
	m_model.Update();
	if (m_status.Set(m_model.GetStatus())) {
		m_view.SetStatus(m_status.Get());
		UpdateResolutionAndAxisIndicators(); // update if state changes
	}

	UpdateDROs();
	UpdateHomed();
	UpdateError();

	m_view.Update();
}

void GrinderController::SelectUnits(Units units) {
	Serial.println("SelectUnits");

    m_units = units;
	UpdateResolutionAndAxisIndicators();
	UpdateLimitDros();
}

void GrinderController::SetOperatingMode(Mode mode) {
	if (m_mode.Set(mode)) {
		Serial.print("ChangeOperatingMode to ");
		Serial.println(static_cast<int>(m_mode.Get()));
		m_view.SetOperatingMode(m_mode.Get());
	}
}

void GrinderController::SelectAxis(Optional<Axis> selectedAxis, Optional<int> resolutionSwitchPosition) {
	Serial.println("SelectAxis");

	m_selectedAxis = selectedAxis;
	m_resolutionSwitchPosition = resolutionSwitchPosition;
	UpdateResolutionAndAxisIndicators();
}

void GrinderController::UpdateResolutionAndAxisIndicators() {
	int32_t resolution = 0;
	if (m_resolutionSwitchPosition.HasValue()) {
		resolution = 1;

		switch (m_resolutionSwitchPosition) {
		case 0:
			resolution = 1000;
			break;
		case 1:
			resolution = 100;
			break;
		case 2:
			resolution = 10;
			break;
		}
		if (m_units == Units::MILLIMETERS) {
			resolution *= 10;
		}
	}

	m_selectedResolution = resolution;

	// check to make sure jogging is allowed by the model/cycle
	Optional<Axis> axis = m_selectedAxis;
	if (axis.HasValue() &&
		!m_model.AllowJog(axis.Value(), ConvertToNm(m_selectedResolution)) ) {
		axis = Optional<Axis>();
	}

	m_view.SetAxisIndicators(axis, m_selectedResolution);
}

void GrinderController::Jog(int32_t clicks) {
	Serial.println("Jog");

	int32_t nmPerClick = ConvertToNm(m_selectedResolution);
	if (m_selectedAxis.HasValue() && m_model.AllowJog(m_selectedAxis.Value(), nmPerClick)) {
		int32_t nanometers = clicks * nmPerClick;
		m_model.JogAxisNm(m_selectedAxis, nanometers);
	}
}

void GrinderController::SetStartLimit(Axis axis) {
	Serial.println("SetStartLimit");

	m_config.GetProcessValues(axis)->startLimit = m_model.GetLastCommandedPositionNm(axis);
	UpdateLimitDros();
}

void GrinderController::SetEndLimit(Axis axis) {
	Serial.println("SetEndLimit");

	m_config.GetProcessValues(axis)->endLimit = m_model.GetLastCommandedPositionNm(axis);
	UpdateLimitDros();
}

void GrinderController::SetSafePosition(Axis axis) {
	Serial.println("SetSafePosition");

	m_config.GetProcessValues(axis)->safePosition = m_model.GetLastCommandedPositionNm(axis);
	UpdateLimitDros();
}

void GrinderController::SetWorkPosition(Axis axis) {
	Serial.println("SetWorkPosition");

	m_config.GetProcessValues(axis)->workPosition = m_model.GetLastCommandedPositionNm(axis);
	UpdateLimitDros();
}

void GrinderController::UpdateLimitDros() {
	for (int i = 0; i < AXIS_COUNT; i++) {
		Axis axis = static_cast<Axis>(i);
		Configuration::ProcessValues *processValues = m_config.GetProcessValues(axis);
		m_view.SetStartDroValue(axis, ApplyOffsetAndConvertToUnits(processValues->startLimit, processValues->droWorkOffset, axis));
		m_view.SetEndDroValue(axis, ApplyOffsetAndConvertToUnits(processValues->endLimit, processValues->droWorkOffset, axis));
		m_view.SetSafeDroValue(axis, ApplyOffsetAndConvertToUnits(processValues->safePosition, processValues->droWorkOffset, axis));
		m_view.SetWorkDroValue(axis, ApplyOffsetAndConvertToUnits(processValues->workPosition, processValues->droWorkOffset, axis));
	}
}

Optional<int32_t> GrinderController::ApplyOffsetAndConvertToUnits(Optional<int32_t> value, int32_t offset, Axis axis) {
	if (value.HasValue()) {
		return Optional<int32_t>(ConvertToUnits(m_model.QuantizePositionNm(axis,value.Value()) - offset));
	}
	return Optional<int32_t>();
}

void GrinderController::SetCycleType(CycleType cycleType) {
	if (m_cycleType.Set(cycleType)) {
		Serial.print("SetCycleType to ");
		Serial.println(static_cast<int>(m_cycleType.Get()));
		m_view.SetCycleType(cycleType);
	}
}

void GrinderController::EnterEstop() {
	Serial.println("EnterEstop");
	m_model.EStop();
}

void GrinderController::ClearEstop() {
	Serial.println("ClearEstop");
	m_model.Init();
}

void GrinderController::CycleStart() {
	Serial.println("CycleStart");

	switch (m_mode.Get()) {
	case Mode::SETUP:
		m_model.CycleStart(m_cycleType.Get());
		break;
	}
}

void GrinderController::CycleStop() {
	Serial.println("CycleStop");
	m_model.CycleStop();
}

void GrinderController::TraverseToStartPosition(Axis axis) {
	Serial.println("TraverseToStartPosition");
	Optional<int32_t> target = m_config.GetProcessValues(axis)->startLimit;
	if (target.HasValue()) {
		m_model.MoveToPosition(axis, target.Value());
	}
}

void GrinderController::TraverseToEndPosition(Axis axis) {
	Serial.println("TraverseToEndPosition");
	Optional<int32_t> target = m_config.GetProcessValues(axis)->endLimit;
	if (target.HasValue()) {
		m_model.MoveToPosition(axis, target.Value());
	}
}

void GrinderController::TraverseToSafePosition(Axis axis) {
	Serial.println("TraverseToSafePosition");
	Optional<int32_t> target = m_config.GetProcessValues(axis)->safePosition;
	if (target.HasValue()) {
		m_model.MoveToPosition(axis, target.Value());
	}
}

void GrinderController::TraverseToWorkPosition(Axis axis) {
	Serial.println("TraverseToWorkPosition");
	Optional<int32_t> target = m_config.GetProcessValues(axis)->workPosition;
	if (target.HasValue()) {
		m_model.MoveToPosition(axis, target.Value());
	}
}


int32_t GrinderController::ConvertToNm(int32_t units) {
	switch (m_units) {
	case Units::MILLIMETERS:
		return units * 10;
	case Units::INCHES:
		return units * 254;
	}
	return 0;
}

int32_t GrinderController::ConvertToUnits(int32_t nanometers) {
	switch (m_units) {
	case Units::MILLIMETERS:
		return nanometers / 10;
	case Units::INCHES:
		return nanometers / 254;
	}
	return 0;
}

void GrinderController::SetWorkOffset(Axis selectedAxis) {
	Serial.println("SetWorkOffset");
	m_config.GetProcessValues(selectedAxis)->droWorkOffset = m_model.GetCurrentPositionNm(selectedAxis);
	UpdateLimitDros();
}

void GrinderController::UpdateDROs() {
	for (int i = 0; i < AXIS_COUNT; i++) {
		Axis axis = static_cast<Axis>(i);
		UpdateDRO(axis);
	}
}

void GrinderController::UpdateHomed() {
	// if the homed state has changed, update the view
	if (m_isHomed.Set(m_model.IsHomed())) {
		m_view.SetIsHomed(m_model.IsHomed());

		// if we're homed, move to touchoff, otherwise default to homing
		SetCycleType(m_isHomed.Get() ? CycleType::TOUCHOFF : CycleType::HOME);
	}
}

void GrinderController::UpdateError() {
	m_view.SetMessage(m_model.Error());
}

void GrinderController::UpdateDRO(Axis axis) {
	int32_t nanometers = m_model.GetCurrentPositionNm(axis);

	int32_t units = ConvertToUnits(nanometers - m_config.GetProcessValues(axis)->droWorkOffset);
	m_view.SetDroValue(axis, units);
}

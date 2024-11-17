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

#include "GrinderController.h"

void GrinderController::Init() {
	// Initialize the model
	m_model.Init();

	// Initialize the view
	m_view.Init(this);

	m_view.SetOperatingMode(m_mode);
}

void GrinderController::Update() {
	m_model.Update();

	UpdateDROs();

	m_view.Update();
}

void GrinderController::SelectUnits(Units units) {
	Serial.println("SelectUnits");

    m_units = units;
	UpdateResolutionAndAxisIndicators();
	UpdateLimitDros();
}

void GrinderController::SetOperatingMode(Mode mode) {
	Serial.println("SetOperatingMode");

	m_mode = mode;
	m_view.SetOperatingMode(m_mode);
}

void GrinderController::SelectAxis(Optional<Axis> selectedAxis, int resolutionSwitchPosition) {
	Serial.println("SelectAxis");

    m_selectedAxis = selectedAxis;
	m_resolutionSwitchPosition = resolutionSwitchPosition;
	UpdateResolutionAndAxisIndicators();
}

void GrinderController::UpdateResolutionAndAxisIndicators() {
	int32_t resolution = 1;
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

	m_selectedResolution = resolution;

	m_view.SetAxisIndicators(m_selectedAxis, m_selectedResolution);
}

void GrinderController::Jog(int32_t clicks) {
	Serial.println("Jog");

	if (m_selectedAxis.HasValue()) {
		int32_t nanometers = ConvertToNm(clicks * m_selectedResolution);
		m_model.JogAxisNm(m_selectedAxis, nanometers);
	}
}

void GrinderController::SetStartLimit(Axis axis) {
	Serial.println("SetStartLimit");

	m_startLimits[static_cast<int>(axis)] = m_model.GetCurrentPositionNm(axis);
	UpdateLimitDros();
}

void GrinderController::SetEndLimit(Axis axis) {
	Serial.println("SetEndLimit");

	m_endLimits[static_cast<int>(axis)] = m_model.GetCurrentPositionNm(axis);
	UpdateLimitDros();
}

void GrinderController::UpdateLimitDros() {
	for (int i = 0; i < AXIS_COUNT; i++) {
		Axis axis = static_cast<Axis>(i);
		m_view.SetStartDroValue(axis, ConvertToUnits(m_startLimits[i] - m_droWorkOffsets[static_cast<int>(axis)]));
		m_view.SetEndDroValue(axis, ConvertToUnits(m_endLimits[i] - m_droWorkOffsets[static_cast<int>(axis)]));
	}
}

void GrinderController::EnterEstop() {
	Serial.println("EnterEstop");
}

void GrinderController::ClearEstop() {
	Serial.println("ClearEstop");

	m_model.ResetAndEnable();
}

void GrinderController::CycleStart() {
	Serial.println("CycleStart");
}

void GrinderController::CycleStop() {
	Serial.println("CycleStop");
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
	m_droWorkOffsets[static_cast<int>(selectedAxis)] = m_model.GetCurrentPositionNm(selectedAxis);
	UpdateLimitDros();
}

void GrinderController::UpdateDROs() {
	for (int i = 0; i < AXIS_COUNT; i++) {
		Axis axis = static_cast<Axis>(i);
		UpdateDRO(axis);
	}
}

void GrinderController::UpdateDRO(Axis axis) {
	int32_t nanometers = m_model.GetCurrentPositionNm(axis);

	int32_t units = ConvertToUnits(nanometers - m_droWorkOffsets[static_cast<int>(axis)]);
	m_view.SetDroValue(axis, units);
}

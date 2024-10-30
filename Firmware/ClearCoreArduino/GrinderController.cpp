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

#include "GrinderController.h"

void GrinderController::Init() {
	// Initialize the model
	m_model.Init();

	// Initialize the view
	m_view.Init(this);
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
}

void GrinderController::SelectAxis(Axis selectedAxis, int resolutionSwitchPosition) {
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

	if (m_selectedAxis != Axis::NONE) {
		int32_t nanometers = ConvertToNm(clicks * m_selectedResolution);
		m_model.JogAxisNm(m_selectedAxis, nanometers);
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
}

void GrinderController::UpdateDROs() {
	for (int i = 0; i < 3; i++) {
		Axis axis = static_cast<Axis>(i);
		UpdateDRO(axis);
	}
}

void GrinderController::UpdateDRO(Axis axis) {
	int32_t nanometers = m_model.GetCurrentPositionNm(axis);

	int32_t units = ConvertToUnits(nanometers - m_droWorkOffsets[static_cast<int>(axis)]);
	m_view.SetDroValue(axis, units);
}

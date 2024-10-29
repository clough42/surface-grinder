// GrinderController.cpp

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
    m_units = units;
	UpdateResolutionAndAxisIndicators();
}

void GrinderController::SelectAxis(Axis selectedAxis, int resolutionSwitchPosition) {
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
	if (m_selectedAxis != Axis::NONE) {
		int32_t nanometers = ConvertToNm(clicks * m_selectedResolution);
		m_model.JogAxisNm(m_selectedAxis, nanometers);
	}
}

void GrinderController::EnterEstop() {
	Serial.println("Entering estop");
}

void GrinderController::ClearEstop() {
	Serial.println("Clearing estop");
	m_model.ResetAndEnable();
}

void GrinderController::CycleStart() {
	Serial.println("Cycle start");
}

void GrinderController::CycleStop() {
	Serial.println("Cycle stop");
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
	Serial.print("UpdateDRO Axis: ");
	Serial.print(static_cast<int>(axis));
	Serial.print(" Position (nm): ");
	Serial.println(nanometers);

	int32_t units = ConvertToUnits(nanometers - m_droWorkOffsets[static_cast<int>(axis)]);
	m_view.SetDroValue(axis, units);
}

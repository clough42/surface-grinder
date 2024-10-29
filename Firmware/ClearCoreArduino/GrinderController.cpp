// GrinderController.cpp

#include "GrinderController.h"

void GrinderController::Init() {
	// Initialize the model
	m_model.Init();

	// Initialize the view
	m_view.Init(this);
}

void GrinderController::Update() {
	// Update the model
	m_model.Update();

	// Update the view
	m_view.Update();
}

void GrinderController::JogAxisNm(int selectedAxis, int jogAmountNm) {
	m_model.JogAxisNm(static_cast<Axis>(selectedAxis), jogAmountNm);
}

void GrinderController::EnterEstop() {
	Serial.println("Entering estop");
}

void GrinderController::ClearEstop() {
	Serial.println("Clearing estop");
	m_model.ResetAndEnable();
}

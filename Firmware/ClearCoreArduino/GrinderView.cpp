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

#include "GrinderView.h"
#include "HMIConstants.h"
#include "IUserActions.h"

GrinderView* GrinderView::s_instance = nullptr;

void GrinderView::Init(IUserActions* controller) {
    m_controller = controller;

    m_jogAxis.Init();
	m_jogResolution.Init();

    m_eStop.Mode(Connector::INPUT_DIGITAL);

    
    EncoderIn.Enable(true);
        
    m_hmiSerial.begin(115200);

    ConnectorCOM1.RtsMode(SerialBase::LINE_ON);
    delay(100);
    ConnectorCOM1.RtsMode(SerialBase::LINE_OFF);
    delay(5000); // let the HMI boot after resetting and show the splash screen before trying to talk to it

    while(!m_genie.Begin(m_hmiSerial));
    while (!m_genie.IsOnline()) delay(100);

    m_genie.AttachEventHandler(GrinderView::HmiEventHandler);

    m_genie.SetForm(HMI::FORM_DRO);
    m_genie.WriteContrast(15);
}

void GrinderView::Update() {
    m_genie.DoEvents();

    UpdateAxisSelectors();
    UpdateEncoder();
    UpdateEstop();
    UpdateCycleButtons();
}

void GrinderView::SetDroValue(Axis axis, int32_t unitsValue) {
    if (unitsValue != m_previousDroValues[static_cast<int>(axis)]) {
	    uint16_t hmiDigitsId = 0;
	    switch (axis) {
	    case Axis::X:
		    hmiDigitsId = HMI::DRO_DIGITS_X;
		    break;
	    case Axis::Y:
		    hmiDigitsId = HMI::DRO_DIGITS_Y;
		    break;
	    case Axis::Z:
		    hmiDigitsId = HMI::DRO_DIGITS_Z;
		    break;
	    }

		m_genie.WriteIntLedDigits(hmiDigitsId, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
		m_previousDroValues[static_cast<int>(axis)] = unitsValue;
	}
}

void GrinderView::SetStartDroValue(Axis axis, int32_t unitsValue) {
	switch (axis) {
	case Axis::X:
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_START_X, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
		break;
	case Axis::Z:
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_START_Z, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
		break;
	}
}

void GrinderView::SetEndDroValue(Axis axis, int32_t unitsValue) {
    switch (axis) {
    case Axis::X:
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_END_X, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
        break;
    case Axis::Z:
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_END_Z, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
        break;
    }
}

void GrinderView::UpdateAxisSelectors() {
    // Check the rsolution and axis selectors
    int axisSwitchPosition = m_jogAxis.GetSwitchPosition();
    int resolutionSwitchPosition = m_jogResolution.GetSwitchPosition();

    if (axisSwitchPosition != m_previousAxisSwitchPosition || resolutionSwitchPosition != m_previousResolutionSwitchPosition) {
        m_controller->SelectAxis(static_cast<Axis>(axisSwitchPosition - 1), resolutionSwitchPosition);
        m_previousAxisSwitchPosition = axisSwitchPosition;
        m_previousResolutionSwitchPosition = resolutionSwitchPosition;
    }
}

void GrinderView::SetAxisIndicators(Axis selectedAxis, int32_t resolution) {
    // reset the encoder, just to keep it in a reasonable range
    EncoderIn.Position(0);
    m_previousEncoderCount = 0;

	// update the axis LEDs
	m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_X, selectedAxis == Axis::X ? 1 : 0);
	m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Y, selectedAxis == Axis::Y ? 1 : 0);
	m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Z, selectedAxis == Axis::Z ? 1 : 0);

	// update the resolution LEDs
    m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1S, selectedAxis != Axis::NONE && resolution == 1 ? 1 : 0);
    m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_10S, selectedAxis != Axis::NONE && resolution == 10 ? 1 : 0);
    m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_100S, selectedAxis != Axis::NONE && resolution == 100 ? 1 : 0);
    m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1000S, selectedAxis != Axis::NONE && resolution == 1000 ? 1 : 0);
    m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_10000S, selectedAxis != Axis::NONE && resolution == 10000 ? 1 : 0);
}

void GrinderView::SetOperatingMode(Mode mode) {
	m_genie.WriteObject(GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_SETUP, mode == Mode::SETUP ? 1 : 0);
	m_genie.WriteObject(GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_FLAT, mode == Mode::FLAT ? 1 : 0);
	m_genie.WriteObject(GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_SIDE, mode == Mode::SIDE ? 1 : 0);
	m_genie.WriteObject(GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_CYLINDER, mode == Mode::CYLINDER ? 1 : 0);
	m_genie.WriteObject(GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_DRESS, mode == Mode::DRESS ? 1 : 0);
}

void GrinderView::UpdateEncoder() {
    int32_t rawEncoderCount = EncoderIn.Position();
    int32_t encoderCount = (rawEncoderCount >= 0 ? rawEncoderCount + 2 : rawEncoderCount - 2) / 4; // divide by four, rounding
    if (encoderCount != m_previousEncoderCount) {
        m_controller->Jog(encoderCount - m_previousEncoderCount);
        m_previousEncoderCount = encoderCount;
    }
}

void GrinderView::UpdateEstop() {
	if (m_eStop.InputFallen()) {
		if (m_controller) {
			m_controller->EnterEstop();
		}
	}
    if (m_eStop.InputRisen()) {
        if (m_controller) {
            m_controller->ClearEstop();
        }
    }
}

void GrinderView::UpdateCycleButtons() {
	if (m_cycleRun.InputRisen()) {
		if (m_controller) {
			m_controller->CycleStart();
		}
	}
	if (m_cycleStop.InputFallen()) {
		if (m_controller) {
			m_controller->CycleStop();
		}
	}
}

void GrinderView::HmiEventHandler() {
    if (s_instance) {
        genieFrame Event;
		s_instance->m_genie.DequeueEvent(&Event);
		s_instance->HandleHmiEvent(Event);
    }
}

void GrinderView::HandleHmiEvent(genieFrame& Event)
{
    // DRO Zero Buttons
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_X)) {
		if (m_controller) m_controller->SetWorkOffset(Axis::X);
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Y)) {
        if (m_controller) m_controller->SetWorkOffset(Axis::Y);
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Z)) {
        if (m_controller) m_controller->SetWorkOffset(Axis::Z);
        return;
    }

	// Limit Set Buttons
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_START_BUTTON_X)) {
		if (m_controller) m_controller->SetStartLimit(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_END_BUTTON_X)) {
		if (m_controller) m_controller->SetEndLimit(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_START_BUTTON_Z)) {
		if (m_controller) m_controller->SetStartLimit(Axis::Z);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_END_BUTTON_Z)) {
		if (m_controller) m_controller->SetEndLimit(Axis::Z);
		return;
	}

    // Unit Selection
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::UNITS_BUTTON)) {
        switch (Event.reportObject.data_lsb) {
        case HMI::UNITS_BUTTON_VAL_INCH:
			if (m_controller) m_controller->SelectUnits(Units::INCHES);
            break;
        case HMI::UNITS_BUTTON_VAL_MM:
			if (m_controller) m_controller->SelectUnits(Units::MILLIMETERS);
            break;
        }
		
        return;
    }

    // Mode Selection
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_SETUP)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::SETUP);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_FLAT)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::FLAT);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_SIDE)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::SIDE);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_CYLINDER)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::CYLINDER);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::MODE_BUTTON_DRESS)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::DRESS);
		return;
	}

    Serial.println("Unknown HMI Event!");
    Serial.print("cmd: ");
    Serial.println(Event.reportObject.cmd);
	Serial.print("object: ");
	Serial.println(Event.reportObject.object);
	Serial.print("index: ");
	Serial.println(Event.reportObject.index);
	Serial.print("data lsb: ");
	Serial.println(Event.reportObject.data_lsb);
    Serial.print("data msb: ");
	Serial.println(Event.reportObject.data_msb);

}

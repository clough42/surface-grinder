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

#include <cstdint>
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

    m_genie.SetForm(HMI::SETUPMODE::FORM_ID);
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
	using namespace HMI::SETUPMODE;
    if (unitsValue != m_previousDroValues[static_cast<int>(axis)]) {
	    uint16_t hmiDigitsId = 0;
	    switch (axis) {
	    case Axis::X:
		    hmiDigitsId = XDro_ID;
		    break;
	    case Axis::Y:
		    hmiDigitsId = YDro_ID;
		    break;
	    case Axis::Z:
		    hmiDigitsId = ZDro_ID;
		    break;
	    }

		m_genie.WriteIntLedDigits(hmiDigitsId, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
		m_previousDroValues[static_cast<int>(axis)] = unitsValue;
	}
}

void GrinderView::SetStartDroValue(Axis axis, int32_t unitsValue) {
	using namespace HMI::SETUPMODE;
	switch (axis) {
	case Axis::X:
        m_genie.WriteIntLedDigits(XStartDRO_ID, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
		break;
	case Axis::Z:
        m_genie.WriteIntLedDigits(ZStartDRO_ID, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
		break;
	}
}

void GrinderView::SetEndDroValue(Axis axis, int32_t unitsValue) {
	using namespace HMI::SETUPMODE;
    switch (axis) {
    case Axis::X:
        m_genie.WriteIntLedDigits(XEndDRO_ID, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
        break;
    case Axis::Z:
        m_genie.WriteIntLedDigits(ZEndDRO_ID, unitsValue * static_cast<int>(m_droDirections[static_cast<int>(axis)]));
        break;
    }
}

void GrinderView::UpdateAxisSelectors() {
    // Check the resolution and axis selectors
    Optional<int> axisSwitchPosition = m_jogAxis.GetSwitchPosition();
    Optional<int> resolutionSwitchPosition = m_jogResolution.GetSwitchPosition();

	if (axisSwitchPosition != m_previousAxisSwitchPosition || resolutionSwitchPosition != m_previousResolutionSwitchPosition) {
		Optional<Axis> selectedAxis = axisSwitchPosition.HasValue() && axisSwitchPosition.Value() != 0 ? Optional<Axis>(static_cast<Axis>(axisSwitchPosition - 1)) : Optional<Axis>();
		m_controller->SelectAxis(selectedAxis, resolutionSwitchPosition);
		m_previousAxisSwitchPosition = axisSwitchPosition;
		m_previousResolutionSwitchPosition = resolutionSwitchPosition;
	}
}

void GrinderView::SetAxisIndicators(Optional<Axis> selectedAxis, int32_t resolution) {
	using namespace HMI::SETUPMODE;

    // reset the encoder, just to keep it in a reasonable range
    EncoderIn.Position(0);
    m_previousEncoderCount = 0;

	// update the axis LEDs
	m_genie.WriteObject(XJog_TYPE, XJog_ID, selectedAxis.HasValue() && selectedAxis.Value() == Axis::X ? 1 : 0);
	m_genie.WriteObject(YJog_TYPE, YJog_ID, selectedAxis.HasValue() && selectedAxis.Value() == Axis::Y ? 1 : 0);
	m_genie.WriteObject(ZJog_TYPE, ZJog_ID, selectedAxis.HasValue() && selectedAxis.Value() == Axis::Z ? 1 : 0);

	// update the resolution LEDs
    m_genie.WriteObject(Resolution1_TYPE, Resolution1_ID, selectedAxis.HasValue() && resolution == 1 ? 1 : 0);
    m_genie.WriteObject(Resolution10_TYPE, Resolution10_ID, selectedAxis.HasValue() && resolution == 10 ? 1 : 0);
    m_genie.WriteObject(Resolution100_TYPE, Resolution100_ID, selectedAxis.HasValue() && resolution == 100 ? 1 : 0);
    m_genie.WriteObject(Resolution1000_TYPE, Resolution1000_ID, selectedAxis.HasValue() && resolution == 1000 ? 1 : 0);
    m_genie.WriteObject(Resolution10000_TYPE, Resolution10000_ID, selectedAxis.HasValue() && resolution == 10000 ? 1 : 0);
}

void GrinderView::SetOperatingMode(Mode mode) {
	using namespace HMI::SETUPMODE;

	switch (mode) {
	case Mode::SETUP:
		m_genie.WriteObject(ModeSetupButton_TYPE, ModeSetupButton_ID, 1);
		break;
	case Mode::FLAT:
		m_genie.WriteObject(ModeFlatButton_TYPE, ModeFlatButton_ID, 1);
		break;
	case Mode::SIDE:
		m_genie.WriteObject(ModeSideButton_TYPE, ModeSideButton_ID, 1);
		break;
	case Mode::CYLINDER:
		m_genie.WriteObject(ModeCylButton_TYPE, ModeCylButton_ID, 1);
		break;
	case Mode::DRESS:
		m_genie.WriteObject(ModeDressButton_TYPE, ModeDressButton_ID, 1);
		break;
	}
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
	using namespace HMI::SETUPMODE;

    // DRO Zero Buttons
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, XZeroButton_TYPE, XZeroButton_ID)) {
		if (m_controller) m_controller->SetWorkOffset(Axis::X);
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, YZeroButton_TYPE, YZeroButton_ID)) {
        if (m_controller) m_controller->SetWorkOffset(Axis::Y);
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ZZeroButton_TYPE, ZZeroButton_ID)) {
        if (m_controller) m_controller->SetWorkOffset(Axis::Z);
        return;
    }

	// Limit Set Buttons
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, XSetStartButton_TYPE, XSetStartButton_ID)) {
		if (m_controller) m_controller->SetStartLimit(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, XSetEndButton_TYPE, XSetEndButton_ID)) {
		if (m_controller) m_controller->SetEndLimit(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ZSetStartButton_TYPE, ZSetStartButton_ID)) {
		if (m_controller) m_controller->SetStartLimit(Axis::Z);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ZSetEndButton_TYPE, ZSetEndButton_ID)) {
		if (m_controller) m_controller->SetEndLimit(Axis::Z);
		return;
	}

    // Unit Selection
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, UnitButton_TYPE, UnitButton_ID)) {
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
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ModeSetupButton_TYPE, ModeSetupButton_ID)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::SETUP);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ModeFlatButton_TYPE, ModeFlatButton_ID)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::FLAT);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ModeSideButton_TYPE, ModeSideButton_ID)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::SIDE);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ModeCylButton_TYPE, ModeCylButton_ID)) {
		if (m_controller) m_controller->SetOperatingMode(Mode::CYLINDER);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, ModeDressButton_TYPE, ModeDressButton_ID)) {
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

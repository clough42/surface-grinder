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

#include <cstdint>
#include "GrinderView.h"
#include "HMIConstants.h"
#include "HMIMap.h"
#include "IUserActions.h"

GrinderView* GrinderView::s_instance = nullptr;

void GrinderView::Init(IUserActions* controller) {
    m_controller = controller;

    m_jogAxis.Init();
	m_jogResolution.Init();

    m_eStop.Mode(Connector::INPUT_DIGITAL);
	    
    EncoderIn.Enable(true);
        
    m_hmiSerial.begin(600000);

    ConnectorCOM1.RtsMode(SerialBase::LINE_ON);
    delay(100);
    ConnectorCOM1.RtsMode(SerialBase::LINE_OFF);
    delay(5000); // let the HMI boot after resetting and show the splash screen before trying to talk to it

	//m_genie.AttachDebugStream(Serial);
    while(!m_genie.Begin(m_hmiSerial));
    while (!m_genie.IsOnline()) delay(100);

    m_genie.AttachEventHandler(GrinderView::HmiEventHandler);

	// put up the mechanics initialization form
    SetForm(HMI::INITMECHANICS::FORM_ID);
    m_genie.WriteContrast(m_config.GetHmiContrast());
}

void GrinderView::Update() {
    m_genie.DoEvents();

	if (m_operatingMode.Get() != Mode::INIT) {
		UpdateAxisSelectors();
		UpdateEncoder();
		UpdateEstop();
		UpdateCycleButtons();
	}
}

void GrinderView::SetDroValue(Axis axis, int32_t unitsValue) {
    if (m_droValues[static_cast<int>(axis)].Set(unitsValue)) {
		WriteDroValue(axis);
	}
}

void GrinderView::WriteDroValue(Axis axis) {
	using namespace HMI::SETUPMODE;
	using namespace HMI::ALLMODES;

	uint16_t hmiDigitsId = 0;
	switch (axis) {
	case Axis::X:
		hmiDigitsId = XDro_ID[m_currentForm];
		break;
	case Axis::Y:
		hmiDigitsId = YDro_ID[m_currentForm];
		break;
	case Axis::Z:
		hmiDigitsId = ZDro_ID[m_currentForm];
		break;
	}

	int32_t unitsValue = m_droValues[static_cast<int>(axis)].Get();
	m_genie.WriteIntLedDigits(hmiDigitsId, unitsValue * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
}

void GrinderView::WriteUnits() {
	m_genie.WriteObject(HMI::SETUPMODE::F0UnitButton_TYPE, HMI::ALLMODES::UnitButton_ID[m_currentForm], m_units.Get() == Units::INCHES ? HMI::UNITS_BUTTON_VAL_INCH : HMI::UNITS_BUTTON_VAL_MM);
}

void GrinderView::SetStartDroValue(Axis axis, Optional<int32_t> unitsValue) {
	if (m_startDroValues[static_cast<int>(axis)].Set(unitsValue)) {
		WriteStartDroValue(axis);
	}
}

void GrinderView::WriteStartDroValue(Axis axis) {
	using namespace HMI::ALLMODES;

	Optional<int32_t> unitsValue = m_startDroValues[static_cast<int>(axis)].Get();

	switch (axis) {
	case Axis::X:
        m_genie.WriteIntLedDigits(XStartDRO_ID[m_currentForm], unitsValue.ValueOr(0) * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
		m_genie.WriteObject(F0XSetStartButton_TYPE, XSetStartButton_ID[m_currentForm], unitsValue.HasValue() ? 1 : 0);
		break;
	case Axis::Z:
        m_genie.WriteIntLedDigits(ZStartDRO_ID[m_currentForm], unitsValue.ValueOr(0) * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
		m_genie.WriteObject(F0ZSetStartButton_TYPE, ZSetStartButton_ID[m_currentForm], unitsValue.HasValue() ? 1 : 0);
		break;
	}
}

void GrinderView::SetEndDroValue(Axis axis, Optional<int32_t> unitsValue) {
	if (m_endDroValues[static_cast<int>(axis)].Set(unitsValue)) {
		WriteEndDroValue(axis);
	}
}

void GrinderView::WriteEndDroValue(Axis axis) {
	using namespace HMI::ALLMODES;

	Optional<int32_t> unitsValue = m_endDroValues[static_cast<int>(axis)].Get();

    switch (axis) {
    case Axis::X:
        m_genie.WriteIntLedDigits(XEndDRO_ID[m_currentForm], unitsValue.ValueOr(0) * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
		m_genie.WriteObject(F0XSetEndButton_TYPE, XSetEndButton_ID[m_currentForm], unitsValue.HasValue() ? 1 : 0);
        break;
    case Axis::Z:
        m_genie.WriteIntLedDigits(ZEndDRO_ID[m_currentForm], unitsValue.ValueOr(0) * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
		m_genie.WriteObject(F0ZSetEndButton_TYPE, ZSetEndButton_ID[m_currentForm], unitsValue.HasValue() ? 1 : 0);
        break;
    }
}

void GrinderView::SetSafeDroValue(Axis axis, Optional<int32_t> unitsValue) {
	if (m_safeDroValues[static_cast<int>(axis)].Set(unitsValue)) {
		WriteSafeDroValue(axis);
	}
}

void GrinderView::WriteSafeDroValue(Axis axis) {
	using namespace HMI::ALLMODES;

	Optional<int32_t> unitsValue = m_safeDroValues[static_cast<int>(axis)].Get();

	switch (axis) {
	case Axis::Y:
		m_genie.WriteIntLedDigits(YSafeDRO_ID[m_currentForm], unitsValue.ValueOr(0) * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
		m_genie.WriteObject(F0YSetSafeButton_TYPE, YSetSafeButton_ID[m_currentForm], unitsValue.HasValue() ? 1 : 0);
		break;
	}
}

void GrinderView::SetWorkDroValue(Axis axis, Optional<int32_t> unitsValue) {
	if (m_workDroValues[static_cast<int>(axis)].Set(unitsValue)) {
		WriteWorkDroValue(axis);
	}
}

void GrinderView::WriteWorkDroValue(Axis axis) {
	using namespace HMI::ALLMODES;

	Optional<int32_t> unitsValue = m_workDroValues[static_cast<int>(axis)].Get();

	switch (axis) {
	case Axis::Y:
		m_genie.WriteIntLedDigits(YWorkDRO_ID[m_currentForm], unitsValue.ValueOr(0) * static_cast<int>(m_config.GetAxisConfig(axis)->droDirection));
		m_genie.WriteObject(F0YSetWorkButton_TYPE, YSetWorkButton_ID[m_currentForm], unitsValue.HasValue() ? 1 : 0);
		break;
	}
}

void GrinderView::SetIsHomed(bool isHomed) {
	if (m_isHomed.Set(isHomed)) {
		WriteIsHomed();
	}
}

void GrinderView::WriteIsHomed() {
	m_genie.WriteObject(HMI::SETUPMODE::F0HomeIndicator_TYPE, HMI::ALLMODES::HomeIndicator_ID[m_currentForm], m_isHomed.Get() ? 1 : 0);
}

void GrinderView::SetMessage(Optional<const char*> message) {
	if (m_message.Set(message)) {
		WriteMessage();
	}
}

void GrinderView::WriteMessage() {
	m_genie.WriteStr(HMI::ALLMODES::Message_ID[m_currentForm], m_message.Get().ValueOr(""));
}

void GrinderView::UpdateAxisSelectors() {
    // Check the resolution and axis selectors
    Optional<int> axisSwitchPosition = m_jogAxis.GetSwitchPosition();
    Optional<int> resolutionSwitchPosition = m_jogResolution.GetSwitchPosition();

	if (m_axisSwitchPosition.Set(axisSwitchPosition) || m_resolutionSwitchPosition.Set(resolutionSwitchPosition)) {
		Optional<Axis> selectedAxis = axisSwitchPosition.HasValue() && axisSwitchPosition.Value() != 0 ? Optional<Axis>(static_cast<Axis>(axisSwitchPosition - 1)) : Optional<Axis>();
		m_controller->SelectAxis(selectedAxis, resolutionSwitchPosition);
	}
}

void GrinderView::SetAxisIndicators(Optional<Axis> selectedAxis, int32_t resolution) {
	bool changed = false;

	changed |= m_selectedAxis.Set(selectedAxis);
	changed |= m_selectedResolution.Set(resolution);

	if (changed) {
		// reset the encoder, just to keep it in a reasonable range
		EncoderIn.Position(0);
		m_previousEncoderCount = 0;

		WriteAxisIndicators();
	}
}

void GrinderView::WriteAxisIndicators() {
	using namespace HMI::SETUPMODE;
	using namespace HMI::ALLMODES;

	int32_t resolution = m_selectedResolution.Get();
	Optional<Axis> selectedAxis = m_selectedAxis.Get();

	// update the axis LEDs
	m_genie.WriteObject(F0XJog_TYPE, XJog_ID[m_currentForm], resolution > 0 && selectedAxis.HasValue() && selectedAxis.Value() == Axis::X ? 1 : 0);
	m_genie.WriteObject(F0YJog_TYPE, YJog_ID[m_currentForm], resolution > 0 && selectedAxis.HasValue() && selectedAxis.Value() == Axis::Y ? 1 : 0);
	m_genie.WriteObject(F0ZJog_TYPE, ZJog_ID[m_currentForm], resolution > 0 && selectedAxis.HasValue() && selectedAxis.Value() == Axis::Z ? 1 : 0);

	// update the resolution LEDs
    m_genie.WriteObject(F0Resolution1_TYPE, Resolution1_ID[m_currentForm], selectedAxis.HasValue() && resolution == 1 ? 1 : 0);
    m_genie.WriteObject(F0Resolution10_TYPE, Resolution10_ID[m_currentForm], selectedAxis.HasValue() && resolution == 10 ? 1 : 0);
    m_genie.WriteObject(F0Resolution100_TYPE, Resolution100_ID[m_currentForm], selectedAxis.HasValue() && resolution == 100 ? 1 : 0);
    m_genie.WriteObject(F0Resolution1000_TYPE, Resolution1000_ID[m_currentForm], selectedAxis.HasValue() && resolution == 1000 ? 1 : 0);
    m_genie.WriteObject(F0Resolution10000_TYPE, Resolution10000_ID[m_currentForm], selectedAxis.HasValue() && resolution == 10000 ? 1 : 0);
}



void GrinderView::SetOperatingMode(Mode mode) {
	using namespace HMI::SETUPMODE;
	using namespace HMI::ALLMODES;

	if (m_operatingMode.Set(mode)) {

		switch (mode) {
		case Mode::SETUP:
			SetForm(HMI::SETUPMODE::FORM_ID);
			m_genie.WriteObject(F0ModeSetupButton_TYPE, ModeSetupButton_ID[m_currentForm], 1);
			break;
		case Mode::FLAT:
			SetForm(HMI::FLATMODE::FORM_ID);
			m_genie.WriteObject(F0ModeFlatButton_TYPE, ModeFlatButton_ID[m_currentForm], 1);
			break;
		case Mode::SIDE:
			SetForm(HMI::SIDEMODE::FORM_ID);
			m_genie.WriteObject(F0ModeSideButton_TYPE, ModeSideButton_ID[m_currentForm], 1);
			break;
		case Mode::CYLINDER:
			SetForm(HMI::CYLMODE::FORM_ID);
			m_genie.WriteObject(F0ModeCylButton_TYPE, ModeCylButton_ID[m_currentForm], 1);
			break;
		case Mode::DRESS:
			SetForm(HMI::DRESSMODE::FORM_ID);
			m_genie.WriteObject(F0ModeDressButton_TYPE, ModeDressButton_ID[m_currentForm], 1);
			break;
		}

		WriteCommonValues();
	}
}

/// <summary>
/// Write all common values out to the HMI after switching forms.
/// </summary>
void GrinderView::WriteCommonValues() {
	WriteDroValue(Axis::X);
	WriteDroValue(Axis::Y);
	WriteDroValue(Axis::Z);
	WriteAxisIndicators();

	WriteUnits();
	WriteStatus();
	WriteIsHomed();
	WriteMessage();

	WriteStartDroValue(Axis::X);
	WriteEndDroValue(Axis::X);
	WriteStartDroValue(Axis::Z);
	WriteEndDroValue(Axis::Z);
	WriteSafeDroValue(Axis::Y);
	WriteWorkDroValue(Axis::Y);
}

void GrinderView::SetForm(int form) {
	ASSERT(form >= 0 && form < 7);
	m_currentForm = form;
	m_genie.SetForm(form);

}

void GrinderView::SetCycleType(CycleType cycleType) {
	using namespace HMI::SETUPMODE;

	if (m_cycleType.Set(cycleType)) {
		switch (cycleType) {
		case CycleType::HOME:
			m_genie.WriteObject(CycleHomeButton_TYPE, CycleHomeButton_ID, 1);
			break;
		case CycleType::TOUCHOFF:
			m_genie.WriteObject(CycleTouchButton_TYPE, CycleTouchButton_ID, 1);
			break;
		}
	}
}


void GrinderView::SetStatus(Status status) {
	if (m_status.Set(status)) {
		WriteStatus();
	}
}

void GrinderView::WriteStatus() {
	using namespace HMI::SETUPMODE;
	using namespace HMI::ALLMODES;

	m_genie.WriteObject(F0StatusImage_TYPE, StatusImage_ID[m_currentForm], static_cast<int>(m_status.Get()));
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
	using namespace HMI::ALLMODES;

    // DRO Zero Buttons
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0XZeroButton_TYPE, XZeroButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetWorkOffset(Axis::X);
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0YZeroButton_TYPE, YZeroButton_ID[m_currentForm])) {
        if (m_controller) m_controller->SetWorkOffset(Axis::Y);
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ZZeroButton_TYPE, ZZeroButton_ID[m_currentForm])) {
        if (m_controller) m_controller->SetWorkOffset(Axis::Z);
        return;
    }

	// Limit Set Buttons
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0XSetStartButton_TYPE, XSetStartButton_ID[m_currentForm])) {
		if (m_controller) {
			m_controller->SetStartLimit(Axis::X);
		}
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0XSetEndButton_TYPE, XSetEndButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetEndLimit(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ZSetStartButton_TYPE, ZSetStartButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetStartLimit(Axis::Z);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ZSetEndButton_TYPE, ZSetEndButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetEndLimit(Axis::Z);
		return;
	}

	// Safe and Work Set Buttons
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0YSetSafeButton_TYPE, YSetSafeButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetSafePosition(Axis::Y);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0YSetWorkButton_TYPE, YSetWorkButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetWorkPosition(Axis::Y);
		return;
	}

	// Respond to Go Right/Left/Up/Down buttons
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GoUpButton_TYPE, GoUpButton_ID)) {
		if (m_controller) m_controller->TraverseToStartPosition(Axis::Z);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GoDownButton_TYPE, GoDownButton_ID)) {
		if (m_controller) m_controller->TraverseToEndPosition(Axis::Z);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GoLeftButton_TYPE, GoLeftButton_ID)) {
		if (m_controller) m_controller->TraverseToStartPosition(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GoRightButton_TYPE, GoRightButton_ID)) {
		if (m_controller) m_controller->TraverseToEndPosition(Axis::X);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GoSafeButton_TYPE, GoSafeButton_ID)) {
		if (m_controller) m_controller->TraverseToSafePosition(Axis::Y);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GoWorkButton_TYPE, GoWorkButton_ID)) {
		if (m_controller) m_controller->TraverseToWorkPosition(Axis::Y);
		return;
	}

    // Unit Selection
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0UnitButton_TYPE, UnitButton_ID[m_currentForm])) {
        switch (Event.reportObject.data_lsb) {
        case HMI::UNITS_BUTTON_VAL_INCH:
			m_units.Set(Units::INCHES);
            break;
        case HMI::UNITS_BUTTON_VAL_MM:
			m_units.Set(Units::MILLIMETERS);
            break;
        }

		if (m_controller) m_controller->SelectUnits(m_units.Get());
		
        return;
    }

    // Mode Selection
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ModeSetupButton_TYPE, ModeSetupButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetOperatingMode(Mode::SETUP);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ModeFlatButton_TYPE, ModeFlatButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetOperatingMode(Mode::FLAT);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ModeSideButton_TYPE, ModeSideButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetOperatingMode(Mode::SIDE);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ModeCylButton_TYPE, ModeCylButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetOperatingMode(Mode::CYLINDER);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, F0ModeDressButton_TYPE, ModeDressButton_ID[m_currentForm])) {
		if (m_controller) m_controller->SetOperatingMode(Mode::DRESS);
		return;
	}

	// Cycle Type Selection
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, CycleHomeButton_TYPE, CycleHomeButton_ID)) {
		if (m_controller) m_controller->SetCycleType(CycleType::HOME);
		return;
	}
	if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, CycleTouchButton_TYPE, CycleTouchButton_ID)) {
		if (m_controller) m_controller->SetCycleType(CycleType::TOUCHOFF);
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

#include "GrinderView.h"
#include "HMIConstants.h"
#include "IViewController.h"

GrinderView* GrinderView::s_instance = nullptr;

void GrinderView::Init(IViewController* controller) {
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

    UpdateDros();
    UpdateJogControls();
    UpdateEstop();

	m_forceHmiUpdate = false; // reset the force update flag
}

void GrinderView::UpdateDros() {
    UpdateDro(Axis::X, HMI::DRO_DIGITS_X);
    UpdateDro(Axis::Y, HMI::DRO_DIGITS_Y);
    UpdateDro(Axis::Z, HMI::DRO_DIGITS_Z);
}

void GrinderView::UpdateDro(Axis axis, int hmiDigitsId) {
    int32_t currentPosition = m_model.GetCurrentPositionNm(axis);
	if (m_forceHmiUpdate || currentPosition != m_previousDroValues[axis]) {
        int32_t currentUnits = ConvertToUnits(currentPosition - m_droWorkOffsets[axis]);
		m_genie.WriteIntLedDigits(hmiDigitsId, currentUnits * m_droDirections[axis]);
		m_previousDroValues[axis] = currentPosition;
	}
}

int32_t GrinderView::ConvertToUnits(int32_t nanometers) {
    switch (m_currentUnits) {
    case Units::MILLIMETERS:
		return nanometers / 10;
    case INCHES:
		return nanometers / 254;   
    }
	return 0;
}

int32_t GrinderView::ConvertToNm(int32_t units) {
    switch (m_currentUnits) {
    case Units::MILLIMETERS:
        return units * 10;
    case INCHES:
        return units * 254;
    }
    return 0;
}

void GrinderView::UpdateJogControls() {
	// Check the rsolution and axis selectors
	int axisSwitchPosition = m_jogAxis.GetSwitchPosition();
    int resolutionSwitchPosition = m_jogResolution.GetSwitchPosition();

    // Only update if a switch has moved, or if we are forcing an HMI update due to some other change
    if (m_forceHmiUpdate || axisSwitchPosition != m_previousAxisSwitchPosition || resolutionSwitchPosition != m_previousResolutionSwitchPosition ) {
        // reset the encoder, just to keep it in a reasonable range
        EncoderIn.Position(0);
        m_previousEncoderCount = 0;

		// update the axis LEDs
		m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_X, axisSwitchPosition == 1 ? 1 : 0);
		m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Y, axisSwitchPosition == 2 ? 1 : 0);
		m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Z, axisSwitchPosition == 3 ? 1 : 0);

		// update the resolution LEDs
        switch (m_currentUnits) {
        case INCHES:
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1S, axisSwitchPosition != 0 && resolutionSwitchPosition == 3 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_10S, axisSwitchPosition != 0 && resolutionSwitchPosition == 2 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_100S, axisSwitchPosition != 0 && resolutionSwitchPosition == 1 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1000S, axisSwitchPosition != 0 && resolutionSwitchPosition == 0 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_10000S, 0);
            break;
        case Units::MILLIMETERS:
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1S, 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_10S, axisSwitchPosition != 0 && resolutionSwitchPosition == 3 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_100S, axisSwitchPosition != 0 && resolutionSwitchPosition == 2 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1000S, axisSwitchPosition != 0 && resolutionSwitchPosition == 1 ? 1 : 0);
            m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_10000S, axisSwitchPosition != 0 && resolutionSwitchPosition == 0 ? 1 : 0);
            break;
        }

        // remember the switch positions for next time
        m_previousAxisSwitchPosition = axisSwitchPosition;
        m_previousResolutionSwitchPosition = resolutionSwitchPosition;
    }

    // only bother messing with the encoder if an axis is selected
    if (axisSwitchPosition > 0) {
		Axis selectedAxis = static_cast<Axis>(axisSwitchPosition - 1);

        // read the encoder and figure out the desired jog amount
        int32_t rawEncoderCount = EncoderIn.Position();
        int32_t encoderCount = (rawEncoderCount >= 0 ? rawEncoderCount + 2 : rawEncoderCount - 2) / 4; // divide by four, rounding
        if (encoderCount != m_previousEncoderCount) {
            int32_t increment = encoderCount - m_previousEncoderCount;

            switch (resolutionSwitchPosition) {
            case 0:
                increment *= 1000;
                break;
            case 1:
                increment *= 100;
                break;
            case 2:
                increment *= 10;
                break;
            }

            if (m_currentUnits == Units::MILLIMETERS) {
                increment *= 10; // Metric resolutions are 10X larger on a pure decimal basis
            }

            int32_t jogAmountNm = ConvertToNm(increment);

            if (m_controller) {
                m_controller->JogAxisNm(selectedAxis, jogAmountNm);
            }

            m_previousEncoderCount = encoderCount;
        }
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
		m_droWorkOffsets[Axis::X] = m_model.GetCurrentPositionNm(Axis::X);
		m_forceHmiUpdate = true;
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Y)) {
        m_droWorkOffsets[Axis::Y] = m_model.GetCurrentPositionNm(Axis::Y);
        m_forceHmiUpdate = true;
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Z)) {
        m_droWorkOffsets[Axis::Z] = m_model.GetCurrentPositionNm(Axis::Z);
        m_forceHmiUpdate = true;
        return;
    }

    // Unit Selection
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::UNITS_BUTTON)) {
        switch (Event.reportObject.data_lsb) {
        case HMI::UNITS_BUTTON_VAL_INCH:
			m_currentUnits = INCHES;
            break;
        case HMI::UNITS_BUTTON_VAL_MM:
			m_currentUnits = Units::MILLIMETERS;
            break;
        }
		
        m_forceHmiUpdate = true;
        return;
    }

    Serial.println("Unknown HMI event: ");

    Serial.print("cmd=");
    Serial.println(Event.reportObject.cmd);
    Serial.print("object=");
    Serial.println(Event.reportObject.object);
    Serial.print("index=");
    Serial.println(Event.reportObject.index);
    Serial.print("lsb=");
    Serial.println(Event.reportObject.data_lsb);
    Serial.print("msb=");
    Serial.println(Event.reportObject.data_msb);
}

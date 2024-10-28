// ControlPanel.cpp
#include "ControlPanel.h"
#include "HMIConstants.h"

GrinderControlPanel* GrinderControlPanel::s_instance = nullptr;

void GrinderControlPanel::Init() {
    m_jogAxis.Init();
	m_jogResolution.Init();

    m_eStop.Mode(Connector::INPUT_DIGITAL);
    m_leftLimit.Mode(Connector::INPUT_DIGITAL);
    m_rightLimit.Mode(Connector::INPUT_DIGITAL);
    
    EncoderIn.Enable(true);
        
    m_hmiSerial.begin(115200);

    ConnectorCOM1.RtsMode(SerialBase::LINE_ON);
    delay(100);
    ConnectorCOM1.RtsMode(SerialBase::LINE_OFF);
    delay(5000); // let the HMI boot after resetting and show the splash screen before trying to talk to it

    while(!m_genie.Begin(m_hmiSerial));
    while (!m_genie.IsOnline()) delay(100);

    m_genie.AttachEventHandler(GrinderControlPanel::HmiEventHandler);

    m_genie.SetForm(HMI::FORM_DRO);
    m_genie.WriteContrast(15);
}

void GrinderControlPanel::Update() {
    m_genie.DoEvents();

    UpdateDros();
    UpdateEncoder();

	//int32_t axis = m_jogAxis.GetSwitchPosition();
 //   int32_t resolution = m_jogResolution.GetSwitchPosition();

 //   if (axis != oldAxis || resolution != oldResolution) {
 //       Serial.print("Axis: ");
 //       Serial.println(axis);
 //       Serial.print("Resolution: ");
 //       Serial.println(resolution);
 //       oldAxis = axis;
 //       oldResolution = resolution;

 //       EncoderIn.Position(0);
 //       oldCount = 0;

 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_X, axis == 1 ? 1 : 0);
 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Y, axis == 2 ? 1 : 0);
 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Z, axis == 3 ? 1 : 0);
 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1S, axis != 0 && resolution == 3 ? 1 : 0);
 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI:: DRO_LED_10S, axis != 0 && resolution == 2 ? 1 : 0);
 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_100S, axis != 0 && resolution == 1 ? 1 : 0);
 //       m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1000S, axis != 0 && resolution == 0 ? 1 : 0);
 //   }
}

void GrinderControlPanel::UpdateDros(bool force) {
    UpdateDro(GrinderModel::X, HMI::DRO_DIGITS_X, force);
    UpdateDro(GrinderModel::Y, HMI::DRO_DIGITS_Y, force);
    UpdateDro(GrinderModel::Z, HMI::DRO_DIGITS_Z, force);
}

void GrinderControlPanel::UpdateDro(GrinderModel::Axis axis, int hmiDigitsId, bool force) {
    int32_t currentPosition = m_model.GetCurrentPositionNm(axis);
	if (force || currentPosition != m_previousDroValues[axis]) {
        Serial.print("DRO Current position (nm): ");
        Serial.println(currentPosition);
        Serial.println();
        int32_t currentUnits = ConvertToUnits(currentPosition);
		m_genie.WriteIntLedDigits(hmiDigitsId, currentUnits * m_droDirections[axis]);
		m_previousDroValues[axis] = currentPosition;
	}
}

int32_t GrinderControlPanel::ConvertToUnits(int32_t nanometers) {
    switch (m_currentUnits) {
	case MILLIMETERS:
		return nanometers / 10;
    case INCHES:
		return nanometers / 254;   
    }
	return 0;
}

int32_t GrinderControlPanel::ConvertToNm(int32_t units) {
    switch (m_currentUnits) {
    case MILLIMETERS:
        return units * 10;
    case INCHES:
        return units * 254;
    }
    return 0;
}

void GrinderControlPanel::UpdateEncoder() {
	int axisSwitchPosition = m_jogAxis.GetSwitchPosition();
    if (axisSwitchPosition != m_previousAxisSwitchPosition) {
        EncoderIn.Position(0); // reset encoder when we switch axes
        m_previousEncoderCount = 0;
		m_previousAxisSwitchPosition = axisSwitchPosition;
    }

    // only bother messing with the encoder if an axis is selected
    if (axisSwitchPosition > 0) {
		GrinderModel::Axis selectedAxis = (GrinderModel::Axis)(axisSwitchPosition - 1);

        // read the encoder and figure out the desired jog amount
        int32_t encoderCount = (EncoderIn.Position() + 2) / 4; // each click is one full quadrature cycle
        if (encoderCount != m_previousEncoderCount) {
            int32_t increment = encoderCount - m_previousEncoderCount;

            switch (m_jogResolution.GetSwitchPosition()) {
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

            if (m_currentUnits == MILLIMETERS) {
                increment *= 10; // Metric resolutions are 10X larger on a pure decimal basis
            }

			int32_t jogAmountNm = ConvertToNm(increment);

            // Debug output
            Serial.print("Selected Axis: ");
            Serial.println(selectedAxis);
            Serial.print("Increment: ");
            Serial.println(increment);
            Serial.print("Jog Amount (nm): ");
            Serial.println(jogAmountNm);
            Serial.println();

			m_model.JogAxisNm(selectedAxis, jogAmountNm);

            m_previousEncoderCount = encoderCount;
        }
    }
}

bool GrinderControlPanel::EStopState()
{
    return m_eStop.State();
}

void GrinderControlPanel::HmiEventHandler() {
    if (s_instance) {
        genieFrame Event;
		s_instance->m_genie.DequeueEvent(&Event);
		s_instance->HandleHmiEvent(Event);
    }
}

void GrinderControlPanel::HandleHmiEvent(genieFrame& Event)
{
    // DRO Zero Buttons
    //if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_X)) {
    //    droX = 0;
    //    updateDros = true;
    //    return;
    //}
    //if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Y)) {
    //    droY = 0;
    //    updateDros = true;
    //    return;
    //}
    //if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Z)) {
    //    droZ = 0;
    //    updateDros = true;
    //    return;
    //}

    // Unit Selection
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::UNITS_BUTTON)) {
        switch (Event.reportObject.data_lsb) {
        case HMI::UNITS_BUTTON_VAL_INCH:
			m_currentUnits = INCHES;
            break;
        case HMI::UNITS_BUTTON_VAL_MM:
			m_currentUnits = MILLIMETERS;
            break;
        }
		UpdateDros(true);
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

int GrinderControlPanel::quadrant(float voltage) {
    return ((int)((voltage * 0.6) + 1)) / 2;
}
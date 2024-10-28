// ControlPanel.cpp
#include "ControlPanel.h"
#include "HMIConstants.h"

int32_t oldCount = 0;
int axis, oldAxis = 0, resolution, oldResolution = 0;
int32_t droX, droY, droZ;
bool updateDros = true;

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

    

    int32_t count = (EncoderIn.Position()) / 4;
    if (count != oldCount) {
        int32_t increment = count - oldCount;
        switch (resolution) {
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
        switch (axis) {
        case 1:
            droX += increment;
            updateDros = true;
            break;
        case 2:
            droY += increment;
            updateDros = true;
            break;
        case 3:
            droZ += increment;
            updateDros = true;
            break;
        }

        oldCount = count;
    }
    if (updateDros) {
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_X, droX);
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_Y, droY);
        m_genie.WriteIntLedDigits(HMI::DRO_DIGITS_Z, droZ);
        updateDros = false;
    }

	axis = m_jogAxis.GetSwitchPosition();
    resolution = m_jogResolution.GetSwitchPosition();

    if (axis != oldAxis || resolution != oldResolution) {
        Serial.print("Axis: ");
        Serial.println(axis);
        Serial.print("Resolution: ");
        Serial.println(resolution);
        oldAxis = axis;
        oldResolution = resolution;

        EncoderIn.Position(0);
        oldCount = 0;

        m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_X, axis == 1 ? 1 : 0);
        m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Y, axis == 2 ? 1 : 0);
        m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_Z, axis == 3 ? 1 : 0);
        m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1S, axis != 0 && resolution == 3 ? 1 : 0);
        m_genie.WriteObject(GENIE_OBJ_ILED, HMI:: DRO_LED_10S, axis != 0 && resolution == 2 ? 1 : 0);
        m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_100S, axis != 0 && resolution == 1 ? 1 : 0);
        m_genie.WriteObject(GENIE_OBJ_ILED, HMI::DRO_LED_1000S, axis != 0 && resolution == 0 ? 1 : 0);
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
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_X)) {
        droX = 0;
        updateDros = true;
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Y)) {
        droY = 0;
        updateDros = true;
        return;
    }
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::DRO_ZERO_BUTTON_Z)) {
        droZ = 0;
        updateDros = true;
        return;
    }

    // Unit Selection
    if (m_genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI::UNITS_BUTTON)) {
        switch (Event.reportObject.data_lsb) {
        case HMI::UNITS_BUTTON_VAL_INCH:
            Serial.println("Switch to Inches");
            return;
        case HMI::UNITS_BUTTON_VAL_MM:
            Serial.println("Switch to Millimeters");
            return;
        }
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
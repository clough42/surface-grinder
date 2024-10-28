// ControlPanel.h
#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <cstdint>
#include <ClearCore.h> // Include the ClearCore library
#include <SerialUsb.h>
#include <genieArduinoDEV.h>
#include "GrinderModel.h"
#include "AnalogSwitch.h"

class GrinderControlPanel {
public:
    GrinderControlPanel(
        DigitalInOut& eStop,
        DigitalInOut& leftLimit,
        DigitalInOut& rightLimit,
        DigitalInOut& cycleRun,
        DigitalInOut& cycleStop,
        DigitalInAnalogIn& jogAxisInput,
        DigitalInAnalogIn& jogResolutionInput,
        Uart& hmiSerial,
        Connector& hmiConnector,
        EncoderInput& encoderIn,
        GrinderModel& model
    ) : m_eStop(eStop),
        m_leftLimit(leftLimit),
        m_rightLimit(rightLimit),
        m_cycleRun(cycleRun),
        m_cycleStop(cycleStop),
        m_hmiSerial(hmiSerial),
        m_hmiConnector(hmiConnector),
        m_encoderIn(encoderIn),
        m_grinderModel(model),
        m_jogAxis(jogAxisInput),
        m_jogResolution(jogResolutionInput)
    {
		s_instance = this;
    }

    void Init();
    void Update();
    bool EStopState();
    void HandleHmiEvent(genieFrame& Event);

private:
    DigitalInOut& m_eStop;
    DigitalInOut& m_leftLimit;
    DigitalInOut& m_rightLimit;
    DigitalInOut& m_cycleRun;
    DigitalInOut& m_cycleStop;
    Uart& m_hmiSerial;
    Connector& m_hmiConnector;
    EncoderInput& m_encoderIn;
    Genie m_genie;

    AnalogSwitch m_jogAxis;
    AnalogSwitch m_jogResolution;

	GrinderModel& m_grinderModel;

    int quadrant(float voltage);

    static void HmiEventHandler();
    static GrinderControlPanel *s_instance;
};

#endif // CONTROL_PANEL_H

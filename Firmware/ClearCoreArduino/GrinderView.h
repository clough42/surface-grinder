#ifndef GRINDER_VIEW_H
#define GRINDER_VIEW_H

#include <cstdint>
#include <ClearCore.h> // Include the ClearCore library
#include <SerialUsb.h>
#include <genieArduinoDEV.h>
#include "IViewData.h"
#include "AnalogSwitch.h"
#include "IUserActions.h"

class GrinderView {
public:

    GrinderView(
        DigitalInOut& eStop,
        DigitalInOut& cycleRun,
        DigitalInOut& cycleStop,
        DigitalInAnalogIn& jogAxisInput,
        DigitalInAnalogIn& jogResolutionInput,
        Uart& hmiSerial,
        Connector& hmiConnector,
        EncoderInput& encoderIn,
        Direction droDirections[3]
    ) : m_eStop(eStop),
        m_cycleRun(cycleRun),
        m_cycleStop(cycleStop),
        m_hmiSerial(hmiSerial),
        m_hmiConnector(hmiConnector),
        m_encoderIn(encoderIn),
        m_jogAxis(jogAxisInput),
        m_jogResolution(jogResolutionInput)
    {
		s_instance = this;
		for (int i = 0; i < 3; i++) {
			m_droDirections[i] = droDirections[i];
		}
    }

    void Init(IUserActions* controller);
    void Update();
    void SetAxisIndicators(Axis selectedAxis, int32_t selectedResolution);
    void SetDroValue(Axis axis, int32_t unitsValue);
    void HandleHmiEvent(genieFrame& Event);

private:
    void UpdateAxisSelectors();
    void UpdateEncoder();
	void UpdateEstop();
    void UpdateCycleButtons();

    // Hardware I/O
    DigitalInOut& m_eStop;
    DigitalInOut& m_cycleRun;
    DigitalInOut& m_cycleStop;
    Connector& m_hmiConnector;
    EncoderInput& m_encoderIn;
    AnalogSwitch m_jogAxis;
    AnalogSwitch m_jogResolution;

    // HMI
    Uart& m_hmiSerial;
    Genie m_genie;

    static void HmiEventHandler();
    static GrinderView *s_instance;

    Direction m_droDirections[3];

    // previous control positions
	int32_t m_previousEncoderCount = 0;
    int32_t m_previousAxisSwitchPosition = 0;
	int32_t m_previousResolutionSwitchPosition = 0;

    // previous HMI element values
    int32_t m_previousDroValues[3] = { 0, 0, 0 };

    // other software components
    IUserActions* m_controller = nullptr;

};

#endif // GRINDER_VIEW_H


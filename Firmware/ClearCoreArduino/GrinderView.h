#ifndef GRINDER_VIEW_H
#define GRINDER_VIEW_H

#include <cstdint>
#include <ClearCore.h> // Include the ClearCore library
#include <SerialUsb.h>
#include <genieArduinoDEV.h>
#include "IViewModel.h"
#include "AnalogSwitch.h"
#include "IViewController.h"

class GrinderView {
public:

    GrinderView(
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
        IViewModel& model,
        Direction droDirections[3]
    ) : m_eStop(eStop),
        m_leftLimit(leftLimit),
        m_rightLimit(rightLimit),
        m_cycleRun(cycleRun),
        m_cycleStop(cycleStop),
        m_hmiSerial(hmiSerial),
        m_hmiConnector(hmiConnector),
        m_encoderIn(encoderIn),
        m_jogAxis(jogAxisInput),
        m_jogResolution(jogResolutionInput),
        m_model(model),
		m_currentUnits(INCHES)
    {
		s_instance = this;
		for (int i = 0; i < 3; i++) {
			m_droDirections[i] = droDirections[i];
		}
    }

    void Init(IViewController* controller);
    void Update();
    void HandleHmiEvent(genieFrame& Event);

private:
    void UpdateDros();
    void UpdateJogControls();
    void UpdateDro(Axis axis, int hmiDigitsId);
	void UpdateEstop();
    int32_t ConvertToUnits(int32_t nanometers); // convert to (units * 2^5)
	int32_t ConvertToNm(int32_t units); // convert from (units * 2^5)

    DigitalInOut& m_eStop;
    DigitalInOut& m_leftLimit;
    DigitalInOut& m_rightLimit;
    DigitalInOut& m_cycleRun;
    DigitalInOut& m_cycleStop;
    Uart& m_hmiSerial;
    Connector& m_hmiConnector;
    EncoderInput& m_encoderIn;

    IViewModel& m_model;
    IViewController* m_controller = nullptr;

    Genie m_genie;
	Units m_currentUnits;

    AnalogSwitch m_jogAxis;
    AnalogSwitch m_jogResolution;

    static void HmiEventHandler();
    static GrinderView *s_instance;

    int32_t m_droDirections[3];

	int32_t m_droWorkOffsets[3] = { 0, 0, 0 };
	int32_t m_previousDroValues[3] = { 0, 0, 0 };
	int32_t m_previousEncoderCount = 0;
    int32_t m_previousAxisSwitchPosition = 0;
	int32_t m_previousResolutionSwitchPosition = 0;
    bool m_forceHmiUpdate = true;
};

#endif // GRINDER_VIEW_H


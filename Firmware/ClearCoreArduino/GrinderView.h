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

#ifndef GRINDER_VIEW_H
#define GRINDER_VIEW_H

#include <cstdint>
#include <ClearCore.h> // Include the ClearCore library
#include <SerialUsb.h>
#include <genieArduinoDEV.h>
#include "AnalogSwitch.h"
#include "IUserActions.h"
#include "CommonEnums.h"
#include "Configuration.h"
#include "TrackedValue.h"

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
        Configuration& config
    ) : m_eStop(eStop),
        m_cycleRun(cycleRun),
        m_cycleStop(cycleStop),
        m_hmiSerial(hmiSerial),
        m_hmiConnector(hmiConnector),
        m_encoderIn(encoderIn),
        m_jogAxis(jogAxisInput),
        m_jogResolution(jogResolutionInput),
        m_config(config),
        m_operatingMode(Mode::INIT),
		m_isHomed(false)
    {
		s_instance = this;
    }

    void Init(IUserActions* controller);
    void Update();
    void SetAxisIndicators(Optional<Axis> selectedAxis, int32_t selectedResolution);
    void SetDroValue(Axis axis, int32_t unitsValue);
	void SetStartDroValue(Axis axis, int32_t unitsValue);
	void SetEndDroValue(Axis axis, int32_t unitsValue);
    void SetSafeDroValue(Axis axis, int32_t unitsValue);
	void SetWorkDroValue(Axis axis, int32_t unitsValue);
	void SetOperatingMode(Mode mode);
    void SetStatus(Status status);
    void SetIsHomed(bool);

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

    Configuration& m_config;

    TrackedValue<Mode> m_operatingMode;

    // previous control positions
	int32_t m_previousEncoderCount = 0;
    Optional<int> m_previousAxisSwitchPosition = 0;
	Optional<int> m_previousResolutionSwitchPosition = 0;

    // previous HMI element values
    int32_t m_previousDroValues[AXIS_COUNT] = { 0, 0, 0 };
    TrackedValue<bool> m_isHomed;

    // other software components
    IUserActions* m_controller = nullptr;

};

#endif // GRINDER_VIEW_H


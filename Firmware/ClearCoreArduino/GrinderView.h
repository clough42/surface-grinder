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

#ifndef GRINDER_VIEW_H
#define GRINDER_VIEW_H

#include <cstdint>
#include <ClearCore.h> // Include the ClearCore library
#include <SerialUsb.h>
#include <genieArduinoDEV.h>
#include "AnalogSwitch.h"
#include "IUserActions.h"
#include "CommonEnums.h"

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
	void SetStartDroValue(Axis axis, int32_t unitsValue);
	void SetEndDroValue(Axis axis, int32_t unitsValue);
	void SetOperatingMode(Mode mode);

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


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

#ifndef GRINDER_VIEW_H
#define GRINDER_VIEW_H

#include <cstdint>
#include <ClearCore.h> // Include the ClearCore library
#include <SerialUsb.h>
#include "genieArduinoCLOUGH.h"
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
        m_cycleType(CycleType::HOME),
        m_isHomed(false),
        m_axisSwitchPosition(Optional<int>()),
        m_resolutionSwitchPosition(Optional<int>()),
        m_currentForm(1),
        m_units(Units::INCHES),
        m_status(Status::IDLE),
		m_selectedAxis(Optional<Axis>()),
		m_selectedResolution(0)
    {
		s_instance = this;
    }

    void Init(IUserActions* controller);
    void Update();

    // Set values to be displayed
    void SetDroValue(Axis axis, int32_t unitsValue);
    void SetUnits(Units units);
    void SetStatus(Status status);
    void SetIsHomed(bool);
    void SetMessage(Optional<const char*> message);
    void SetAxisIndicators(Optional<Axis> selectedAxis, int32_t selectedResolution);
	void SetStartDroValue(Axis axis, Optional<int32_t> unitsValue);
	void SetEndDroValue(Axis axis, Optional<int32_t> unitsValue);
    void SetSafeDroValue(Axis axis, Optional<int32_t> unitsValue);
	void SetWorkDroValue(Axis axis, Optional<int32_t> unitsValue);
    
    void SetRoughDepth(int index, int32_t unitsValue);
	void SetFinishDepth(int index, int32_t unitsValue);
    void SetRoughCount(int count);
    void SetFinishCount(int count);
    void SetSparkCount(int count);
    void SetAutoGrind(boolean enabled);

	void SetOperatingMode(Mode mode);

	void SetCycleType(CycleType cycleType);

    void HandleHmiEvent(genieFrame& Event);

private:
    // Write mirror values to the HMI
    void WriteDroValue(Axis axis);
    void WriteUnits();
    void WriteStatus();
    void WriteIsHomed();
    void WriteMessage();
    void WriteAxisIndicators();
    void WriteStartDroValue(Axis axis);
	void WriteEndDroValue(Axis axis);
	void WriteSafeDroValue(Axis axis);
	void WriteWorkDroValue(Axis axis);
    void WriteRoughDepth();
    void WriteFinishDepth();
	void WriteRoughCount();
	void WriteFinishCount();
	void WriteSparkCount();
	void WriteAutoGrind();

    // Write all of the common values when switching forms
    void WriteCommonValues();

    void UpdateAxisSelectors();
    void UpdateEncoder();
	void UpdateEstop();
    void UpdateCycleButtons();
    void SetForm(int form);

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
    int m_currentForm;

    static void HmiEventHandler();
    static GrinderView *s_instance;

    Configuration& m_config;

    // previous control positions
	int32_t m_previousEncoderCount = 0;
    TrackedValue<Optional<int>> m_axisSwitchPosition;
	TrackedValue<Optional<int>> m_resolutionSwitchPosition;

    // HMI Value Mirror Registers
    TrackedValue<int32_t> m_droValues[AXIS_COUNT] = { 0, 0, 0 };
	TrackedValue<Units> m_units;
    TrackedValue<Status> m_status;
    TrackedValue<bool> m_isHomed;
    TrackedValue<Optional<const char*>> m_message;
	TrackedValue<Optional<Axis>> m_selectedAxis;
	TrackedValue<int32_t> m_selectedResolution;
	TrackedValue<Optional<int32_t>> m_startDroValues[AXIS_COUNT] = { Optional<int32_t>(), Optional<int32_t>(), Optional<int32_t>() };
	TrackedValue<Optional<int32_t>> m_endDroValues[AXIS_COUNT] = { Optional<int32_t>(), Optional<int32_t>(), Optional<int32_t>() };
	TrackedValue<Optional<int32_t>> m_safeDroValues[AXIS_COUNT] = { Optional<int32_t>(), Optional<int32_t>(), Optional<int32_t>() };
	TrackedValue<Optional<int32_t>> m_workDroValues[AXIS_COUNT] = { Optional<int32_t>(), Optional<int32_t>(), Optional<int32_t>() };
    TrackedValue<int> m_roughDepthIndex;
    TrackedValue<int16_t> m_roughDepthUnitsValue;
	TrackedValue<int> m_finishDepthIndex;
	TrackedValue<int16_t> m_finishDepthUnitsValue;
	TrackedValue<int> m_roughCount;
	TrackedValue<int> m_finishCount;
    TrackedValue<int> m_sparkCount;
	TrackedValue<bool> m_autoGrind;

    TrackedValue<Mode> m_operatingMode;
    TrackedValue<CycleType> m_cycleType;

    // other software components
    IUserActions* m_controller = nullptr;

};

#endif // GRINDER_VIEW_H


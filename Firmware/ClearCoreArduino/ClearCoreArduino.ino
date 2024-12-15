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

#include <sd-examples.h>
#include <cstdint>

#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>
#include <SerialUsb.h>

#include <genieArduinoDEV.h>

#include "Configuration.h"
#include "MachineAxis.h"
#include "GrinderModel.h"
#include "GrinderView.h"
#include "GrinderController.h"
#include "CommonEnums.h"
#include "CycleHoming.h"
#include "Assert.h"

// Dependency Injection
namespace Injected {

	auto& RedLED = ConnectorLed;

	// Configuration
	Configuration config("configuration.txt");

	// Axes
	MachineAxis axes[AXIS_COUNT] = {
		MachineAxis(ConnectorM0, 3, 130175, CLEARCORE_PIN_IO0, Direction::NEGATIVE, Direction::NEGATIVE),	// X
		MachineAxis(ConnectorM1, 6, 3175, CLEARCORE_PIN_IO0, Direction::NEGATIVE, Direction::POSITIVE),		// Y
		MachineAxis(ConnectorM2, 3, 6350, CLEARCORE_PIN_IO0, Direction::NEGATIVE, Direction::POSITIVE)		// Z
	};

	// Cycles
	CycleHoming homingCycle = CycleHoming(axes);
	Cycle *cycles[] = {
		&homingCycle
	};
	int cycleCount = sizeof(cycles) / sizeof(cycles[0]);

	// Model
	GrinderModel Model(
		axes,			// X, Y, and Z Axes
		cycles,
		cycleCount,
		ConnectorIO1,	// Left Limit
		ConnectorIO2	// Right Limit Switch
	);

	// View
	Direction droDirections[AXIS_COUNT] = { Direction::NEGATIVE, Direction::POSITIVE, Direction::POSITIVE };
	GrinderView View(
		ConnectorIO0,	// ESTOP
		ConnectorIO3,	// Cycle Run
		ConnectorIO4,	// Cycle Stop
		ConnectorA9,	// Jog Axis
		ConnectorA10,	// Jog Resolution
		Serial1,		// HMI Serial Port
		ConnectorCOM1,	// HMI Serial Connector
		EncoderIn,		// Encoder Input
		droDirections	// DRO Directions
	);

	// Controller
	GrinderController Controller(Model, View);

}

void setup() {
	// Red LED on while initializing
	Injected::RedLED.Mode(Connector::OUTPUT_DIGITAL);
	Injected::RedLED.State(true);

	// serial port for debugging
	Serial.begin(9600);
		
	MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);
	MotorMgr.MotorModeSet(MotorManager::MOTOR_ALL, Connector::CPM_MODE_STEP_AND_DIR);

	Injected::Controller.Init(); // also initializes model and view

	// Red LED off at the end
	Injected::RedLED.State(false);
}

void loop() {
	Injected::Controller.Update();
}







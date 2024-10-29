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

#include <cstdint>

#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>
#include <SerialUsb.h>

#include <genieArduinoDEV.h>

#include "MachineAxis.h"
#include "GrinderModel.h"
#include "GrinderView.h"
#include "GrinderController.h"
#include "CommonEnums.h"

// Dependency Injection
namespace Injected {

	auto& RedLED = ConnectorLed;

	// Model
	MachineAxis XAxis(ConnectorM0, 3, 130175, CLEARCORE_PIN_IO0, Direction::REVERSE);
	MachineAxis YAxis(ConnectorM1, 6, 3175, CLEARCORE_PIN_IO0, Direction::REVERSE);
	MachineAxis ZAxis(ConnectorM2, 3, 6350, CLEARCORE_PIN_IO0, Direction::REVERSE);
	MachineAxis* axes[3] = { &XAxis, &YAxis, &ZAxis };
	GrinderModel Model(
		axes,			// X, Y, and Z Axes
		ConnectorIO1,	// Left Limit
		ConnectorIO2	// Right Limit Switch
	);

	// View
	Direction droDirections[3] = { Direction::REVERSE, Direction::NORMAL, Direction::NORMAL };
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







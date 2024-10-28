#include <cstdint>

#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>
#include <SerialUsb.h>

#include <genieArduinoDEV.h>

#include "MachineAxis.h"
#include "ControlPanel.h"
#include "GrinderController.h"

auto& RedLED = ConnectorLed;

MachineAxis XAxis(ConnectorM0, 3, 130175, CLEARCORE_PIN_IO0, MachineAxis::REVERSE);
MachineAxis YAxis(ConnectorM1, 6, 3175, CLEARCORE_PIN_IO0, MachineAxis::REVERSE);
MachineAxis ZAxis(ConnectorM2, 3, 6350, CLEARCORE_PIN_IO0, MachineAxis::REVERSE);

// Model
MachineAxis* axes[3] = { &XAxis, &YAxis, &ZAxis };
GrinderModel Model(axes);

// View
GrinderControlPanel::DroDirection droDirections[3] = { GrinderControlPanel::DOWN, GrinderControlPanel::UP, GrinderControlPanel::UP };
GrinderControlPanel ControlPanel(
	ConnectorIO0,	// ESTOP
	ConnectorIO1,	// Left Limit
	ConnectorIO2,	// Right Limit Switch
	ConnectorIO3,	// Cycle Run
	ConnectorIO4,	// Cycle Stop
	ConnectorA9,	// Jog Axis
	ConnectorA10,	// Jog Resolution
	Serial1,		// HMI Serial Port
	ConnectorCOM1,	// HMI Serial Connector
	EncoderIn,		// Encoder Input
	Model,			// Model
	droDirections	// DRO Directions
);

// Controller
GrinderController Controller(Model, ControlPanel);

int32_t targetPosition = 1000;
bool inEstop = false;

void setup() {
	// Red LED on while initializing
	RedLED.Mode(Connector::OUTPUT_DIGITAL);
	RedLED.State(true);

	// serial port for debugging
	Serial.begin(9600);
		
	MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);
	MotorMgr.MotorModeSet(MotorManager::MOTOR_ALL, Connector::CPM_MODE_STEP_AND_DIR);

	Controller.Init(); // also initializes model and view

	// Red LED off at the end
	RedLED.State(false);
}

void loop() {
	Controller.Update();
}







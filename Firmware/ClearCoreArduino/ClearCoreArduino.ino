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







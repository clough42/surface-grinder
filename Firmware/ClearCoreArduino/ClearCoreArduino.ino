#include <cstdint>

#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>
#include <SerialUsb.h>

#include <genieArduinoDEV.h>

#include "MachineAxis.h"
#include "ControlPanel.h"

auto& RedLED = ConnectorLed;

MachineAxis XAxis(ConnectorM0, 1, 1, CLEARCORE_PIN_IO0);
MachineAxis YAxis(ConnectorM1, 1, 1, CLEARCORE_PIN_IO0);
MachineAxis ZAxis(ConnectorM2, 1, 1, CLEARCORE_PIN_IO0);

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
	EncoderIn		// Encoder Input
);

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

	XAxis.Init();
	YAxis.Init();
	ZAxis.Init();

	ControlPanel.Init();

	// Red LED off at the end
	RedLED.State(false);
}

void loop() {
	ControlPanel.Update();
    	
	Serial.print("Current/Target position: ");
	Serial.print(XAxis.GetPositionInNanometers());
	Serial.print("/");
	Serial.println(targetPosition);

	bool estopButton = ControlPanel.EStopState();
	if( estopButton != inEstop )  {
		if (estopButton) {
			XAxis.ClearAlerts();
			XAxis.Move(targetPosition);
		}
		inEstop = estopButton;
	}
	/*if( ! RightLimit.State() && ! LeftLimit.State() ) {
 		XMotor.MoveStopDecel(0);
 		return;
 	}
 		
 	if( ! LeftLimit.State() ) {
 		currentMove = MoveDirection::MOVING_RIGHT;
 	}
 	else if( ! RightLimit.State() ) {
 		currentMove = MoveDirection::MOVING_LEFT;
 	}*/

	if (XAxis.IsMoveComplete()) {
		targetPosition = -targetPosition;
		XAxis.Move(targetPosition);
	}

}







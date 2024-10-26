#include <cstdint>

#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>
#include <SerialUsb.h>

#include <genieArduinoDEV.h>

#include "HMIConstants.h"
#include "MachineAxis.h"

MachineAxis XAxis(ConnectorM0, 1, 1, CLEARCORE_PIN_IO0);
MachineAxis YAxis(ConnectorM1, 1, 1, CLEARCORE_PIN_IO0);
MachineAxis ZAxis(ConnectorM2, 1, 1, CLEARCORE_PIN_IO0);

auto& RedLED = ConnectorLed;
auto& EStop = ConnectorIO0;
auto& LeftLimit = ConnectorIO1;
auto& RightLimit = ConnectorIO2;
auto& CycleRun = ConnectorIO3;
auto& CycleStop = ConnectorIO4;
auto& JogAxis = ConnectorA9;
auto& JogResolution = ConnectorA10;
auto& Console = Serial;
auto& HMI = Serial1;

Genie genie;

int32_t targetPosition = 1000;

int32_t oldCount = 0;
int axis, oldAxis = 0, resolution, oldResolution = 0;

int sendCount = 0;

int32_t droX, droY, droZ;
bool updateDros = true;

bool inEstop = false;

void setup() {
	RedLED.Mode(Connector::OUTPUT_DIGITAL);
	RedLED.State(true);

	Console.begin(9600);

	EStop.Mode(Connector::INPUT_DIGITAL);
	LeftLimit.Mode(Connector::INPUT_DIGITAL);
	RightLimit.Mode(Connector::INPUT_DIGITAL);
	
	JogAxis.Mode(Connector::INPUT_ANALOG);
	JogResolution.Mode(Connector::INPUT_ANALOG);
	EncoderIn.Enable(true);
		
	MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);
	MotorMgr.MotorModeSet(MotorManager::MOTOR_ALL, Connector::CPM_MODE_STEP_AND_DIR);

	XAxis.initHardware();
	YAxis.initHardware();
	ZAxis.initHardware();

	HMI.begin(115200);

	ConnectorCOM1.RtsMode(SerialBase::LINE_ON);
	delay(100);
	ConnectorCOM1.RtsMode(SerialBase::LINE_OFF);
	delay(5000); // let the HMI boot after resetting and show the splash screen before trying to talk to it

	while(!genie.Begin(HMI));
	while (!genie.IsOnline()) delay(100);

	genie.AttachEventHandler(hmiEventHandler);

	genie.SetForm(HMI_FORM_DRO);
	genie.WriteContrast(15);

	RedLED.State(false);
}

void loop() {
    genie.DoEvents();
	
	int32_t count = (EncoderIn.Position())/4;
    if( count != oldCount ) {
		int32_t increment = count - oldCount;
		switch (resolution) {
		case 0:
			increment *= 1000;
			break;
		case 1:
			increment *= 100;
			break;
		case 2:
			increment *= 10;
			break;
		}
		switch (axis) {
		case 1:
			droX += increment;
			updateDros = true;
			break;
		case 2:
			droY += increment;
			updateDros = true;
			break;
		case 3:
			droZ += increment;
			updateDros = true;
			break;
		}

      oldCount = count;
    }
	if (updateDros) {
		genie.WriteIntLedDigits(HMI_DRO_DIGITS_X, droX);
		genie.WriteIntLedDigits(HMI_DRO_DIGITS_Y, droY);
		genie.WriteIntLedDigits(HMI_DRO_DIGITS_Z, droZ);
		updateDros = false;
	}

	axis = quadrant(JogAxis.AnalogVoltage());
	resolution = quadrant(JogResolution.AnalogVoltage());

	if (abs(axis - oldAxis) > 0.5 || abs(resolution - oldResolution) > 0.5) {
		Console.print("Axis: ");
		Console.println(axis);
		Console.print("Resolution: ");
		Console.println(resolution);
		oldAxis = axis;
		oldResolution = resolution;

		EncoderIn.Position(0);
		oldCount = 0;

		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_X, axis == 1 ? 1 : 0);
		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_Y, axis == 2 ? 1 : 0);
		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_Z, axis == 3 ? 1 : 0);
		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_1S, axis != 0 && resolution == 3 ? 1 : 0);
		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_10S, axis != 0 && resolution == 2 ? 1 : 0);
		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_100S, axis != 0 && resolution == 1 ? 1 : 0);
		genie.WriteObject(GENIE_OBJ_ILED, HMI_DRO_LED_1000S, axis != 0 && resolution == 0 ? 1 : 0);
	}

	Console.print("Current/Target position: ");
	Console.print(XAxis.GetPositionInNanometers());
	Console.print("/");
	Console.println(targetPosition);

	bool estopButton = EStop.State();
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

int quadrant(float voltage) {
	return ((int)((voltage * 0.6) + 1)) / 2;
}


void hmiEventHandler(void)
{
  genieFrame Event;
  genie.DequeueEvent(&Event);

  // DRO Zero Buttons
  if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI_DRO_ZERO_BUTTON_X)) {
	  droX = 0;
	  updateDros = true;
	  return;
  }
  if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI_DRO_ZERO_BUTTON_Y)) {
	  droY = 0;
	  updateDros = true;
	  return;
  }
  if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI_DRO_ZERO_BUTTON_Z)) {
	  droZ = 0;
	  updateDros = true;
	  return;
  }
 
  // Unit Selection
  if (genie.EventIs(&Event, GENIE_REPORT_EVENT, GENIE_OBJ_WINBUTTON, HMI_UNITS_BUTTON)) {
	  switch (Event.reportObject.data_lsb) {
	  case HMI_UNITS_BUTTON_VAL_INCH:
		  Console.println("Switch to Inches");
		  return;
	  case HMI_UNITS_BUTTON_VAL_MM:
		  Console.println("Switch to Millimeters");
		  return;

	  }
  }

  Console.println("Unknown HMI event: ");

  Console.print("cmd=");
  Console.println(Event.reportObject.cmd);
  Console.print("object=");
  Console.println(Event.reportObject.object);
  Console.print("index=");
  Console.println(Event.reportObject.index);
  Console.print("lsb=");
  Console.println(Event.reportObject.data_lsb);
  Console.print("msb=");
  Console.println(Event.reportObject.data_msb);

}


#include <cstdint>

#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>
#include <SerialUsb.h>

#include <genieArduinoDEV.h>

#define STEPS_PER_REV 1000
#define SECONDS_PER_MINUTE 60
#define RPM * STEPS_PER_REV / SECONDS_PER_MINUTE
#define RIGHT * -1
#define LEFT * 1

int32_t velocity = 100 RPM;
int32_t acceleration = 5000 RPM; // per second

auto& LED = ConnectorLed;
auto& EStop = ConnectorIO0;
auto& LeftLimit = ConnectorIO1;
auto& RightLimit = ConnectorIO2;
auto& CycleRun = ConnectorIO3;
auto& CycleStop = ConnectorIO4;
auto& JogAxis = ConnectorA9;
auto& JogResolution = ConnectorA10;
auto& Console = Serial;
auto& HMI = Serial0;

Genie genie;

auto& XMotor = ConnectorM0;

enum class MoveDirection { MOVING_RIGHT, MOVING_LEFT };

MoveDirection currentMove = MoveDirection::MOVING_RIGHT;

int32_t count = 0, oldCount = 0;

void setup() {
  Console.begin(9600);

  EStop.Mode(Connector::INPUT_DIGITAL);
	LeftLimit.Mode(Connector::INPUT_DIGITAL);
	RightLimit.Mode(Connector::INPUT_DIGITAL);
	
  JogAxis.Mode(Connector::INPUT_ANALOG);
  JogResolution.Mode(Connector::INPUT_ANALOG);
	EncoderIn.Enable(true);
		
	MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);
	MotorMgr.MotorModeSet(MotorManager::MOTOR_M0M1, Connector::CPM_MODE_STEP_AND_DIR);
	
	XMotor.EnableRequest(true);
	
	XMotor.AccelMax(acceleration);
	XMotor.MoveStopDecel(0);

  HMI.begin(200000);
  while(!genie.Begin(HMI)) {
    Console.println("Waiting for HMI...");
  }
  genie.AttachEventHandler(hmiEventHandler);
  genie.SetForm(0);
}

void loop() {
    genie.DoEvents();

		count = EncoderIn.Position();
    if( count != oldCount ) {
      genie.WriteIntLedDigits(0,count/4);
      oldCount = count;
    }

    //Console.print("Axis: ");
    //Console.println(JogAxis.AnalogVoltage());
    //Console.print("Resolution: ");
    //Console.println(JogResolution.AnalogVoltage());

		if( ! EStop.State() ) {
			XMotor.MoveStopDecel(0);
			return;
		}
 		if( ! RightLimit.State() && ! LeftLimit.State() ) {
 			XMotor.MoveStopDecel(0);
 			return;
 		}
 		
 		if( ! LeftLimit.State() ) {
 			currentMove = MoveDirection::MOVING_RIGHT;
 		}
 		else if( ! RightLimit.State() ) {
 			currentMove = MoveDirection::MOVING_LEFT;
 		}

		switch(currentMove) {
			case MoveDirection::MOVING_RIGHT:
				XMotor.MoveVelocity(velocity RIGHT);
				break;
				
			case MoveDirection::MOVING_LEFT:
				XMotor.MoveVelocity(velocity LEFT);
				break;
				
			default:
				XMotor.MoveStopDecel(0);
		}
}

void hmiEventHandler(void)
{
  Console.println("Got HMI event");

  genieFrame Event;
  genie.DequeueEvent(&Event);

  Console.print("Object: ");
  Console.println(Event.reportObject.object);
  Console.print("Cmd: ");
  Console.println(Event.reportObject.cmd);
  Console.print("Index: ");
  Console.println(Event.reportObject.index);
  Console.print("Data: ");
  Console.print(Event.reportObject.data_lsb);
  Console.print(" ");
  Console.print(Event.reportObject.data_msb);
}

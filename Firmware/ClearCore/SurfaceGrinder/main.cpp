
#include <ClearCore.h>
#include <DigitalInOut.h>
#include <MotorDriver.h>

#define STEPS_PER_REV 1000
#define SECONDS_PER_MINUTE 60
#define RPM * STEPS_PER_REV / SECONDS_PER_MINUTE
#define RIGHT * -1
#define LEFT * 1

int32_t velocity = 100 RPM;
int32_t acceleration = 5000 RPM; // per second

DigitalInOut *EStop = &ConnectorIO1;
DigitalInOut *LeftLimit = &ConnectorIO2;
DigitalInOut *RightLimit = &ConnectorIO3;

MotorDriver *XMotor = &ConnectorM0;

typedef enum {
	MOVING_RIGHT,
	MOVING_LEFT
	} MoveDirection;


int main(void) {
	EStop->Mode(Connector::INPUT_DIGITAL);
	LeftLimit->Mode(Connector::INPUT_DIGITAL);
	RightLimit->Mode(Connector::INPUT_DIGITAL);
	
	MotorMgr.MotorInputClocking(MotorManager::CLOCK_RATE_NORMAL);
	MotorMgr.MotorModeSet(MotorManager::MOTOR_M0M1, Connector::CPM_MODE_STEP_AND_DIR);
	
	XMotor->EnableRequest(true);
	
	XMotor->AccelMax(acceleration);
	XMotor->MoveStopDecel(0);
	
	MoveDirection currentMove = MOVING_RIGHT;
	
    while (1)
    {
		if( ! EStop->State() ) {
			XMotor->MoveStopDecel(0);
			continue;
		}
		if( ! RightLimit->State() && ! LeftLimit->State() ) {
			XMotor->MoveStopDecel(0);
			continue;
		}
		
		if( ! LeftLimit->State() ) {
			currentMove = MOVING_RIGHT;
		}
		else if( ! RightLimit->State() ) {
			currentMove = MOVING_LEFT;
		}

		switch(currentMove) {
			case MOVING_RIGHT:
				XMotor->MoveVelocity(velocity RIGHT);
				break;
				
			case MOVING_LEFT:
				XMotor->MoveVelocity(velocity LEFT);
				break;
				
			default:
				XMotor->MoveStopDecel(0);
		}
    }
}
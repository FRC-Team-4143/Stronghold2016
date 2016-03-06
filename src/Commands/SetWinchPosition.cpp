#include <Commands/SetWinchPosition.h>
#include "../Robot.h"

SetWinchPosition::SetWinchPosition(int pos)
{
	Requires(Robot::winchSub);
	SetWinchPosition::pos = pos;
	SetTimeout(0.5);
}

// Called just before this Command runs the first time
void SetWinchPosition::Initialize()
{
	if (Robot::winchSub->angleSensor){
		if (pos == 0) Robot::winchSub->setPos(2.85);
		if (pos == 1) Robot::winchSub->setPos(3.14);
		if (pos == 2) Robot::winchSub->setPos(3.44);
	} else {
		if (pos == 0) Robot::winchSub->setPos(0.0);
		if (pos == 1) Robot::winchSub->setPos(0.1);
		if (pos == 2) Robot::winchSub->setPos(0.8);
	}

}

// Called repeatedly when this Command is scheduled to run
void SetWinchPosition::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SetWinchPosition::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void SetWinchPosition::End()
{
	Robot::winchSub->disablePositionControl();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWinchPosition::Interrupted()
{
	End();
}

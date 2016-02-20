#include <Commands/SetWinchPosition.h>
#include "../Robot.h"

SetWinchPosition::SetWinchPosition(double pos, bool disable)
{
	Requires(Robot::winchSub);
	SetWinchPosition::pos = pos;
	SetWinchPosition::disable = disable;
	SetTimeout(0.5);
}

// Called just before this Command runs the first time
void SetWinchPosition::Initialize()
{
	Robot::winchSub->setPos(pos);
/*
if (pos == 0.0) Robot::winchSub->setPos(SmartDashboard::GetNumber("Starting Position", 0.0));
if (pos == 1.0) Robot::winchSub->setPos(SmartDashboard::GetNumber("High Shot Position", 0.0));
if (pos == 2.0) Robot::winchSub->setPos(SmartDashboard::GetNumber("Low Shot Position", 0.0));
*/
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
	if (disable) Robot::winchSub->disablePositionControl();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWinchPosition::Interrupted()
{
	End();
}

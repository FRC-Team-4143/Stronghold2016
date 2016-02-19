#include <Commands/SetWinchPosition.h>
#include "../Robot.h"

SetWinchPosition::SetWinchPosition(double pos)
{
	Requires(Robot::winchSub);
	SetWinchPosition::pos = pos;
}

// Called just before this Command runs the first time
void SetWinchPosition::Initialize()
{
	//Robot::winchSub->setPos(pos);

if (pos == 1) Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch pos 1", 0.0));
if (pos == 2) Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch pos 2", 0.0));
if (pos == 3) Robot::winchSub->setPos(SmartDashboard::GetNumber("Winch pos 3", 0.0));
}

// Called repeatedly when this Command is scheduled to run
void SetWinchPosition::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SetWinchPosition::IsFinished()
{
	return false;
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

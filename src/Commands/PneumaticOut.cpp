#include "PneumaticOut.h"
#include "../Robot.h"

PneumaticOut::PneumaticOut()
{
	Requires(Robot::pickup);
}

// Called just before this Command runs the first time
void PneumaticOut::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PneumaticOut::Execute()
{
	Robot::pickup->PushOut();
}

// Make this return true when this Command no longer needs to run execute()
bool PneumaticOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PneumaticOut::End()
{
	Robot::pickup->PushStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PneumaticOut::Interrupted()
{
	Robot::pickup->PushStop();
}

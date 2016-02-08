#include "PneumaticIn.h"
#include "../Robot.h"

PneumaticIn::PneumaticIn()
{
	Requires(Robot::pickup);
}

// Called just before this Command runs the first time
void PneumaticIn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void PneumaticIn::Execute()
{
	Robot::pickup->PushIn();
}

// Make this return true when this Command no longer needs to run execute()
bool PneumaticIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PneumaticIn::End()
{
	Robot::pickup->PushStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PneumaticIn::Interrupted()
{
	Robot::pickup->PushStop();
}

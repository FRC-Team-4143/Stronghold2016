#include "Shoot.h"
#include "../Robot.h"

Shoot::Shoot(bool stop, double time, double speed)
{
	SetTimeout(time);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	Robot::shooter->shootFront();
	Robot::shooter->shootBack();
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void Shoot::End()
{
	if (stop){
		Robot::shooter->stopFront();
		Robot::shooter->stopBack();
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted()
{
	End();
}

#include "DeFeed.h"
#include "../Robot.h"

DeFeed::DeFeed()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::shooter);
}

// Called just before this Command runs the first time
void DeFeed::Initialize()
{
	Robot::shooter->deFeed();
}

// Called repeatedly when this Command is scheduled to run
void DeFeed::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DeFeed::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DeFeed::End()
{
	Robot::shooter->stopFeed();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeFeed::Interrupted()
{
	End();
}

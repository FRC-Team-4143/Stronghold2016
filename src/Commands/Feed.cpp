#include "Feed.h"
#include "../Robot.h"

Feed::Feed(double Timeout)
{
	SetTimeout(Timeout);
	Requires(Robot::shooter);
}

// Called just before this Command runs the first time
void Feed::Initialize()
{
Robot::shooter->feed();
}

// Called repeatedly when this Command is scheduled to run
void Feed::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Feed::IsFinished()
{
	return IsTimedOut();// || Robot::shooter->feederSensor->GetAverageVoltage() < 4.0;
}

// Called once after isFinished returns true
void Feed::End()
{
	Robot::shooter->stopFeed();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Feed::Interrupted()
{
End();
}

#include "ResetSteeringEncoders.h"
#include "../Robot.h"

ResetSteeringEncoders::ResetSteeringEncoders()
{
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void ResetSteeringEncoders::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ResetSteeringEncoders::Execute()
{
	Robot::driveTrain->zeroSteeringEncoders();
}

// Make this return true when this Command no longer needs to run execute()
bool ResetSteeringEncoders::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ResetSteeringEncoders::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetSteeringEncoders::Interrupted()
{

}

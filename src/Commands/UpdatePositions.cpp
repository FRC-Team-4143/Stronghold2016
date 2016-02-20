#include "UpdatePositions.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

UpdatePositions::UpdatePositions()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void UpdatePositions::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void UpdatePositions::Execute()
{
	Robot::armSub->readPos();
	Robot::winchSub->readPos();
	SmartDashboard::PutBoolean("input test", RobotMap::test->Get());
}

// Make this return true when this Command no longer needs to run execute()
bool UpdatePositions::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void UpdatePositions::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpdatePositions::Interrupted()
{

}
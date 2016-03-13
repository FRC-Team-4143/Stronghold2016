#include "BackupToCenter.h"
#include "../Robot.h"

BackupToCenter::BackupToCenter()
{
	Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void BackupToCenter::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void BackupToCenter::Execute()
{
	auto speed = Robot::visionBridge->GetDistance() * 0.01;
	speed = std::min(std::max(speed, -0.5), 0.5);
	Robot::driveTrain->FieldCentricCrab(0, speed, 0, false);
}

// Make this return true when this Command no longer needs to run execute()
bool BackupToCenter::IsFinished()
{
	return (std::abs(Robot::visionBridge->GetDistance()) < 20);
}

// Called once after isFinished returns true
void BackupToCenter::End()
{
	Robot::driveTrain->Crab(0, 0, 0, false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BackupToCenter::Interrupted()
{
	End();
}
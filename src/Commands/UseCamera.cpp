#include "UseCamera.h"
#include "Robot.h"

UseCamera::UseCamera()
{
	Requires(Robot::cameraSub);
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void UseCamera::Initialize()
{
	Robot::cameraSub->StartCamera();
}

// Called repeatedly when this Command is scheduled to run
void UseCamera::Execute()
{
	Robot::cameraSub->ShowCamera();
}

// Make this return true when this Command no longer needs to run execute()
bool UseCamera::IsFinished()
{
	return Robot::oi->GetButtonStart();
}

// Called once after isFinished returns true
void UseCamera::End()
{
	Robot::cameraSub->StopCamera();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UseCamera::Interrupted()
{
	Robot::cameraSub->StopCamera();
}

#include "UnwindWheels.h"
#include "Robot.h"

UnwindWheels::UnwindWheels()
{
	//Use Requires() here to declare subsystem dependencies
	Requires(Robot::driveTrain);

	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void UnwindWheels::Initialize()
{
bool doneUnwinding = false;
}

// Called repeatedly when this Command is scheduled to run
void UnwindWheels::Execute()
{
doneUnwinding = !Robot::driveTrain->unwind();

}

// Make this return true when this Command no longer needs to run execute()
bool UnwindWheels::IsFinished()
{
	return doneUnwinding;
}

// Called once after isFinished returns true
void UnwindWheels::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UnwindWheels::Interrupted()
{

}

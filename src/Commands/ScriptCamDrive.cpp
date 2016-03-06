#include "ScriptCamDrive.h"
#include "../Robot.h"
#include <iostream>

#define TIME   10

ScriptCamDrive::ScriptCamDrive(const char* name, double x, double y, double maxspeed, double seconds)
: Command(name), _x(x), _y(y), _maxspeed(maxspeed), _seconds(seconds)
{
	std::cout << GetName() << "::ctor(" << x << ", " << y << ", " << maxspeed << ", " << seconds << ")" << std::endl;
	Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void ScriptCamDrive::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_seconds);
	_angle = Robot::gyroSub->PIDGet();
	_angle /= 90.;
	_angle = floor(_angle + .5); // round
	_angle *= 90.;
	_p = SmartDashboard::GetNumber("vision P", .003);
	_tol = SmartDashboard::GetNumber("vision tol", 15);
	_center = SmartDashboard::GetNumber("vision center", 0.0);
	_time = 0;
}

// Called repeatedly when this Command is scheduled to run
void ScriptCamDrive::Execute()
{
	_offset = Robot::visionBridge->GetPosition();
	_offset -= _center;
	if(fabs(_offset) <= _tol)
		_offset = 0;
	Robot::driveTrain->GyroCrab(_angle, _x,
			std::min(_maxspeed, std::max(-_maxspeed, (_offset) * _p)), false);
	if(fabs(_offset) <= _tol)
		_time++;
	else
		_time = 0;
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptCamDrive::IsFinished()
{
	if (_x == 0.0 && _time > TIME)    //fabs(_offset) <= _tol)
		return true;
	return IsTimedOut();
}

// Called once after isFinished returns true
void ScriptCamDrive::End()
{
	std::cout << GetName() << "::End" << std::endl;
	Robot::driveTrain->Crab(0, 0, 0, false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptCamDrive::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
	Robot::driveTrain->Crab(0, 0, 0, false);
}

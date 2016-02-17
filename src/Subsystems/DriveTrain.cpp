#include "DriveTrain.h"
#include "../Modules/Logger.h"
#include "../RobotMap.h"
#include "../Commands/CrabDrive.h"
#include "../Robot.h"

#ifdef TESTSWERVE
#define MAXTURNS 3
#else
#define MAXTURNS 3
#define SOFTTURNLIMIT 1
#endif

const float TWISTSCALE = .5;

const float DEAD_ZONE = 0.2;

//#define GYROP  .05
#define GYROP	.07
#define GYROMAX  .65

DriveTrain::DriveTrain(): Subsystem("DriveTrain") {
	LOG("DriveTrain::DriveTrain");

	frontLeft       = RobotMap::driveTrainFrontLeft;
	frontLeftDrive  = RobotMap::driveTrainFrontLeftDrive;
	frontLeftPos    = RobotMap::driveTrainFrontLeftPos;
	frontLeftSteer  = RobotMap::driveTrainFrontLeftSteer;

	frontRight      = RobotMap::driveTrainFrontRight;
	frontRightDrive = RobotMap::driveTrainFrontRightDrive;
	frontRightPos   = RobotMap::driveTrainFrontRightPos;
	frontRightSteer = RobotMap::driveTrainFrontRightSteer;

	rearLeft        = RobotMap::driveTrainRearLeft;
	rearLeftDrive   = RobotMap::driveTrainRearLeftDrive;
	rearLeftPos     = RobotMap::driveTrainRearLeftPos;
	rearLeftSteer   = RobotMap::driveTrainRearLeftSteer;

	rearRight       = RobotMap::driveTrainRearRight;
	rearRightDrive  = RobotMap::driveTrainRearRightDrive;
	rearRightPos    = RobotMap::driveTrainRearRightPos;
	rearRightSteer  = RobotMap::driveTrainRearRightSteer;

	lastx = 0.0;
	lasty = 0.0;
	lasttwist = 0.0;

	FLInv = 1;
	FRInv = 1;
	RRInv = 1;
	RLInv = 1;
	DriveBackFlag = false;
	robotangle = 0;
	unwinding = false;

	FLValue = 0;
	FRValue = 0;
	RLValue = 0;
	RRValue = 0;
}

void DriveTrain::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new CrabDrive());

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::SetWheelbase(float w, float x, float y) {
	W=w;
	X=x;
	Y=y;
}
void DriveTrain::SetOffsets(double FLOff, double FROff, double RLOff, double RROff) {
	FLOffset = FLOff;
	FROffset = FROff;
	RLOffset = RLOff;
	RROffset = RROff;
}


bool DriveTrain::unwindwheel(AnalogChannelVolt * wheel, PIDController * pid){

	float temp;
	float turns = wheel->getturns();
	if(turns >= 1) {
		temp = wheel->GetAverageVoltage() - 1.0;
		if(temp < 0.0) temp = 5.0 + temp;
		pid->SetSetpoint(temp);
		return true;
	} else
	if(turns <= -1) {
		temp = wheel->GetAverageVoltage() + 1.0;
		if(temp > 5.0) temp = temp - 5.0;
		pid->SetSetpoint(temp);
		return true;
	} else return false;

}

bool DriveTrain::unwind(float y, float x){
	/*
	bool retval = true;
	unwinding = true;
	robotangle = 0;
	if(!(unwindwheel(frontLeftPos, frontLeft) || unwindwheel(frontRightPos, frontRight) ||
			unwindwheel(rearLeftPos, rearLeft) || unwindwheel(rearRightPos, rearRight)))
	{
		unwinding = 0;
		retval = 0;
	}
 	return retval;
 	*/
	frontLeftSteer->SetSetpoint(0);
	frontRightSteer->SetSetpoint(0);
	rearLeftSteer->SetSetpoint(0);
	rearRightSteer->SetSetpoint(0);

	if (y > 0.1){
		frontLeftDrive->Set(-1);
		frontRightDrive->Set(-1);
		rearLeftDrive->Set(-1);
		rearRightDrive->Set(-1);
	} else if (y < -0.1){
		frontLeftDrive->Set(1);
		frontRightDrive->Set(1);
		rearLeftDrive->Set(1);
		rearRightDrive->Set(1);
	} else if (x > 0.1){
		frontLeftDrive->Set(1);
		frontRightDrive->Set(-1);
		rearLeftDrive->Set(1);
		rearRightDrive->Set(-1);
	} else if (x < 0.1){
		frontLeftDrive->Set(-1);
		frontRightDrive->Set(1);
		rearLeftDrive->Set(-1);
		rearRightDrive->Set(1);
	} else {
		frontLeftDrive->Set(0);
		frontRightDrive->Set(0);
		rearLeftDrive->Set(0);
		rearRightDrive->Set(0);
	}
	return false;
}

void DriveTrain::doneunwind(){
	unwinding = 0;
}

// keeps controls consistent regardless of rotation of robot
void DriveTrain::FieldCentricCrab(float twist, float y, float x, bool operatorControl) {
	float FWD = y;
	float STR = x;

	robotangle = (Robot::gyroSub->PIDGet())*pi/180;

	FWD = y*cos(robotangle) + x*sin(robotangle);
	STR = -y*sin(robotangle) + x*cos(robotangle);

	Crab(twist, FWD, STR, operatorControl);
}

// attempts to keep robot square to the field as it drives
void DriveTrain::GyroCrab(float desiredangle, float y, float x, bool operatorControl) {
	robotangle = Robot::gyroSub->PIDGet();
	//std::cout << "robotangle " << robotangle << std::endl;

	float twist = desiredangle - robotangle;
	while( twist > 180.0)
		twist -= 360.0;
	while( twist < -180.0)
		twist += 360.0;

	twist = std::min(GYROMAX, std::max(-GYROMAX, twist * GYROP));
	//std::cout << "twist " << twist << std::endl;
	Crab(twist, y, x, operatorControl);
}

void DriveTrain::Crab(float twist, float y, float x, bool operatorControl) {
	SmartDashboard::PutNumber("Steering Motor Encoder FR", frontRightPos->PIDGet());
	SmartDashboard::PutNumber("Steering Motor Encoder FL", frontLeftPos->PIDGet());
	SmartDashboard::PutNumber("Steering Motor Encoder RR", rearRightPos->PIDGet());
	SmartDashboard::PutNumber("Steering Motor Encoder RL", rearLeftPos->PIDGet());

	SmartDashboard::PutNumber("Steering Motor Turns FR", frontRightPos->getturns());
	SmartDashboard::PutNumber("Steering Motor Turns FL", frontLeftPos->getturns());
	SmartDashboard::PutNumber("Steering Motor Turns RR", rearRightPos->getturns());
	SmartDashboard::PutNumber("Steering Motor Turns RL", rearLeftPos->getturns());

	// stop PID loop if wires wrap.
	if(unwinding ||
		abs(frontRightPos->getturns()) > MAXTURNS ||
		abs(rearRightPos->getturns()) > MAXTURNS ||
		abs(frontLeftPos->getturns()) > MAXTURNS ||
		abs(rearLeftPos->getturns()) > MAXTURNS)
	{
		SetDriveSpeed(0,0,0,0);
		return;
	}

	// this stores the direction of joystick when all axis last crossed into the deadzone
	// and keeps the wheels pointed that direction
	// this .1 should be kept the same as the deadzone in oi.cpp
	if (operatorControl && x == 0.0 && y == 0.0 && twist == 0.0) {
		if (fabs(lasty) > DEAD_ZONE || fabs(lastx) > DEAD_ZONE || fabs(lasttwist) > DEAD_ZONE) {
			y = std::min(std::max(lasty, -DEAD_ZONE), DEAD_ZONE);
			x = std::min(std::max(lastx, -DEAD_ZONE), DEAD_ZONE);
			twist = std::min(std::max(lasttwist, -DEAD_ZONE), DEAD_ZONE);
		} else {
			y = .05; // default wheel position
		}
	}
	lastx = x;
	lasty = y;
	lasttwist = twist;

	if (operatorControl) {
		// scale for operator control
		x *= 1.0;
		y *= 1.0;
		twist *= TWISTSCALE;
	}
	
	float FWD = y;
	float STR = x;

//	FWD = y*cos(robotangle) + x*sin(robotangle);
//	STR = -y*sin(robotangle) + x*cos(robotangle);

//	radius = sqrt(pow(2*Y,2)+pow(X,2));
	radius = sqrt(pow(Y,2)+pow(X,2));

	AP = STR - twist*X/radius;
	BP = STR + twist*X/radius;
//	CP = FWD - twist*2*Y/radius;
//	DP = FWD + twist*2*Y/radius;
	CP = FWD - twist*Y/radius;
	DP = FWD + twist*Y/radius;

	float FLSetPoint = 2.5;
	float FRSetPoint = 2.5;
	float RLSetPoint = 2.5;
	float RRSetPoint = 2.5;

	if(DP != 0 || BP != 0)
		FLSetPoint = (2.5 + 2.5/pi*atan2(BP,DP));
	if(BP != 0 || CP != 0)	
		FRSetPoint = (2.5 + 2.5/pi*atan2(BP,CP));
	if(AP != 0 || DP != 0)
		RLSetPoint = (2.5 + 2.5/pi*atan2(AP,DP));
	if(AP != 0 || CP != 0)
		RRSetPoint = (2.5 + 2.5/pi*atan2(AP,CP));

	SetSteerSetpoint(FLSetPoint, FRSetPoint, RLSetPoint, RRSetPoint);

	FL = sqrt(pow(BP,2)+pow(DP,2));
	FR = sqrt(pow(BP,2)+pow(CP,2));
	RL = sqrt(pow(AP,2)+pow(DP,2));
	RR = sqrt(pow(AP,2)+pow(CP,2));

	//Solve for fastest wheel speed
	double speedarray[] = {fabs(FL), fabs(FR), fabs(RL), fabs(RR)};

	 int length = 4;
     double maxspeed = speedarray[0];
     for(int i = 1; i < length; i++)
     {
		if (speedarray[i] > maxspeed)
			maxspeed = speedarray[i];
     }

	//Set ratios based on maximum wheel speed
    if(maxspeed > 1 || maxspeed < -1)
    {
		FLRatio = FL/maxspeed;
		FRRatio = FR/maxspeed;
		RLRatio = RL/maxspeed;
		RRRatio = RR/maxspeed;
    }
    else
    {
		FLRatio = FL;
		FRRatio = FR;
		RLRatio = RL;
		RRRatio = RR;
	}
	//if(y > 0.049 && y < .051)

	if (operatorControl && fabs(x) <= DEAD_ZONE && fabs(y) <= DEAD_ZONE && fabs(twist) <= DEAD_ZONE) {
		FLRatio = 0.0;
		FRRatio = 0.0;
		RLRatio = 0.0;
		RRRatio = 0.0;
	}

	//Set drive speeds
	SetDriveSpeed(FLRatio, -FRRatio, RLRatio, -RRRatio);
}

double DriveTrain::CorrectSteerSetpoint(double setpoint) {
	if (setpoint < 0) {
		return (setpoint + 5) ;
	}
	else if (setpoint > 5) {
		return (setpoint - 5);
	}
	else if (setpoint == 5) {
		return 0;
	}
	else {
		return setpoint;
	}
}

void DriveTrain::SetSteerSetpoint(float FLSetPoint, float FRSetPoint, float RLSetPoint, float RRSetPoint) {
	//if(driveFront) {
//////////////////////////////////
//Front Left Wheel
//////////////////////////////////
		if(frontLeftSteer->GetPosition() > SOFTTURNLIMIT)
		{
			if (CorrectSteerSetpoint(FLSetPoint + FLOffset - frontLeftPos->GetAverageVoltage()) > 2.5)
			{
				frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset));
				FLInv = 1;
        	} else
        	{
        		frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset - 2.5));
        		FLInv = -1;
        	}
		} else if (frontLeftSteer->GetPosition() < -SOFTTURNLIMIT)
		{
			if (CorrectSteerSetpoint(FLSetPoint + FLOffset - frontLeftPos->GetAverageVoltage()) < 2.5)
			{
				frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset));
				FLInv = 1;
			} else
			{
				frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset - 2.5));
				FLInv = -1;
			}
		} else {
			//Default rotation logic
			if(fabs(FLSetPoint + FLOffset - frontLeftPos->GetAverageVoltage()) < 1.25 || fabs(FLSetPoint + FLOffset - frontLeftPos->GetAverageVoltage()) > 3.75)
			{
				frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset));
				FLInv = 1;
			}
				else
			{
				frontLeft->SetSetpoint(CorrectSteerSetpoint(FLSetPoint + FLOffset-2.5));
				FLInv = -1;
			}
		}
//////////////////////////////////
//Front Right Wheel
//////////////////////////////////
		
		if(frontRightSteer->GetPosition() > SOFTTURNLIMIT)
		{
			if (CorrectSteerSetpoint(FRSetPoint + FROffset - frontLeftPos->GetAverageVoltage()) > 2.5)
			{
				frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset));
				FRInv = 1;
			} else
			{
				frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset - 2.5));
				FRInv = -1;
			}
		} else if (frontRightSteer->GetPosition() < -SOFTTURNLIMIT)
		{
			if (CorrectSteerSetpoint(FRSetPoint + FROffset - frontRightPos->GetAverageVoltage()) < 2.5)
			{
				frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset));
				FRInv = 1;
			} else
			{

				frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset - 2.5));
				FRInv = -1;
			}

		} else
		{
			//default rotation logic
			if(fabs(FRSetPoint + FROffset - frontRightPos->GetAverageVoltage()) < 1.25 || fabs(FRSetPoint + FROffset - frontRightPos->GetAverageVoltage()) > 3.75)
			{
				frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset));
				FRInv = 1;
			}
				else
			{
				frontRight->SetSetpoint(CorrectSteerSetpoint(FRSetPoint + FROffset-2.5));
				FRInv = -1;
			}
		}
//////////////////////////////////
//Rear Left Wheel
//////////////////////////////////
		
		if(rearLeftSteer->GetPosition() > SOFTTURNLIMIT){
			if (CorrectSteerSetpoint(RLSetPoint + RLOffset - rearLeftPos->GetAverageVoltage()) > 2.5)
			{
				rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset));
				RLInv = 1;
			} else
			{

				rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset - 2.5));
				RLInv = -1;
			}
		} else if (rearLeftSteer->GetPosition() < -SOFTTURNLIMIT){
			if (CorrectSteerSetpoint(RLSetPoint + RLOffset - rearLeftPos->GetAverageVoltage()) < 2.5)
			{
				rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset));
				RLInv = 1;
			} else
			{

				rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset - 2.5));
				RLInv = -1;
			}
		} else {
			//default rotation logic
			if(fabs(RLSetPoint + RLOffset - rearLeftPos->GetAverageVoltage()) < 1.25 || fabs(RLSetPoint + RLOffset - rearLeftPos->GetAverageVoltage()) > 3.75)
			{
				rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset));
				RLInv = 1;
			}

				else
			{
				rearLeft->SetSetpoint(CorrectSteerSetpoint(RLSetPoint + RLOffset-2.5));
				RLInv = -1;
			}
		}
		
//////////////////////////////////
//Rear Right Wheel
//////////////////////////////////
		if(rearRightSteer->GetPosition() > SOFTTURNLIMIT){
			if (CorrectSteerSetpoint(RRSetPoint + RROffset - rearRightPos->GetAverageVoltage()) > 2.5)
			{
				rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset));
				RRInv = 1;
			} else
			{

				rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset - 2.5));
				RRInv = -1;
			}
		} else if (rearRightSteer->GetPosition() < -SOFTTURNLIMIT){
			if (CorrectSteerSetpoint(RRSetPoint + RROffset - rearRightPos->GetAverageVoltage()) < 2.5)
			{
				rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset));
				RRInv = 1;
			} else
			{

				rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset - 2.5));
				RRInv = -1;
			}
		} else {
			//default rotation logic
			if(fabs(RRSetPoint + RROffset - rearRightPos->GetAverageVoltage()) < 1.25 || fabs(RRSetPoint + RROffset - rearRightPos->GetAverageVoltage()) > 3.75)
			{
				rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset));
				RRInv = 1;
			}
				else
			{
				rearRight->SetSetpoint(CorrectSteerSetpoint(RRSetPoint + RROffset-2.5));
				RRInv = -1;
			}
		}
	
}

void DriveTrain::SetDriveSpeed(float FLSpeed, float FRSpeed, float RLSpeed, float RRSpeed) {

		frontLeftDrive->Set(FLSpeed*FLInv);
		frontRightDrive->Set(FRSpeed*FRInv);
		rearLeftDrive->Set(RLSpeed*RLInv);
		rearRightDrive->Set(RRSpeed*RRInv);
}

void DriveTrain::Lock() {
	SetSteerSetpoint(3.0, 1.5, 3.0, 1.5);
	SetDriveSpeed(0,0,0,0);
}

void DriveTrain::SideLock() {
	SetSteerSetpoint(2.0, 0.75, 3.25, 4.5);
	SetDriveSpeed(0,0,0,0);
}

bool DriveTrain::ResetTurns() {
	frontRight->Enable();
	rearRight->Enable();
	frontLeft->Enable();
	rearLeft->Enable();
	frontRightPos->ResetTurns();;
	frontLeftPos->ResetTurns();;
	rearRightPos->ResetTurns();;
	rearLeftPos->ResetTurns();;
	robotangle = 0;
	return true;
}

bool DriveTrain::GetDriveBackFlag() {
	return DriveBackFlag;
}

void DriveTrain::SetDriveBackFlag(bool flag) {
	DriveBackFlag = flag;
}

void DriveTrain::updateDistanceEncoders() {
	FLValue = frontLeftDrive->GetEncPosition();
	FRValue = frontRightDrive->GetEncPosition();
	RLValue = rearLeftDrive->GetEncPosition();
	RRValue = rearRightDrive->GetEncPosition();
}

double DriveTrain::getDistanceEncodersValues() {
	double average = (FLValue + FRValue + RLValue + RRValue)/4;
	return average;
}

void DriveTrain::zeroDistanceEncoders() {
	frontLeftDrive->SetPosition(0);
	frontRightDrive->SetPosition(0);
	rearLeftDrive->SetPosition(0);
	rearRightDrive->SetPosition(0);

}

void DriveTrain::zeroSteeringEncoders() {
	frontLeftSteer->SetPosition(0);
	frontRightSteer->SetPosition(0);
	rearLeftSteer->SetPosition(0);
	rearRightSteer->SetPosition(0);

}

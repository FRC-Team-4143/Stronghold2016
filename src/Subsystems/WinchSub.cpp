#include "WinchSub.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

WinchSub::WinchSub() :
		Subsystem("ExampleSubsystem")
{
	motor = RobotMap::winchMotor;
	shooterSensor = RobotMap::winchPot;
	shooter = RobotMap::shooterWinch;

	motor->SetControlMode(CANSpeedController::kPosition);
	motor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	motor->SetP(0.8);
	motor->SetI(0.0);
	motor->SetD(0.05);
	motor->SetF(0.0);
	motor->Enable();
	motor->ConfigPeakOutputVoltage(6.0,-6.0);

}

void WinchSub::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void WinchSub::setPos(double pos){
	motor->SetControlMode(CANSpeedController::kPosition);
	motor->SetSetpoint(pos);
	//shooter->SetSetpoint(pos);
}

void WinchSub::disablePositionControl(){
	motor->SetControlMode(CANSpeedController::kPercentVbus);
}

void WinchSub::readPos(){
	SmartDashboard::PutNumber("Winch Position", motor->GetPosition());
	SmartDashboard::PutNumber("Winch Angle", shooterSensor->GetAverageVoltage());
}

void WinchSub::reset(){
	motor->SetPosition(0.0);
}

#include "ArmSub.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

 ArmSub::ArmSub() : Subsystem("Arm") {
 	armMotor = RobotMap::armMotor;


 	armMotor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
 	armMotor->SetP(0.8);
 	armMotor->SetI(0.0);
 	armMotor->SetD(0.05);
    armMotor->SetF(0.0);
    //armMotor->SetSensorDirection(true);
 	armMotor->SetSetpoint(0.0);
 	armMotor->ConfigPeakOutputVoltage(10.0, -10.0);
 	armMotor->SetControlMode(CANSpeedController::kPosition);

 }

 void ArmSub::InitDefaultCommand() {
     // Set the default command for a subsystem here.
     // SetDefaultCommand(new MySpecialCommand());
 }
 void ArmSub::armDown() {
	 armMotor->SetSetpoint(0.67);
 }
 void ArmSub::stop() {
 	//ArmSub::armMotor->Set(0);
 }
 void ArmSub::armUp() {
	 armMotor->SetSetpoint(0.43);
 }

 void ArmSub::stowArm(){
	 armMotor->SetSetpoint(0.0);
 }

 void ArmSub::readPos(){
	 SmartDashboard::PutNumber("Arm Position", armMotor->GetPosition());
 }

 void ArmSub::reset(){
	 armMotor->SetPosition(0.0);
 }

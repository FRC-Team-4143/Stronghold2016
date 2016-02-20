#include "ArmSub.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"

 ArmSub::ArmSub() : Subsystem("Arm") {
 	armMotor = RobotMap::armMotor;

 	armMotor->SetControlMode(CANSpeedController::kPosition);
 	armMotor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
 	armMotor->SetP(0.8);
 	armMotor->SetI(0.0);
 	armMotor->SetD(0.05);
    armMotor->SetF(0.0);
 	armMotor->Enable();
 	armMotor->ConfigPeakOutputVoltage(6.0,-6.0);
 }

 void ArmSub::InitDefaultCommand() {
     // Set the default command for a subsystem here.
     // SetDefaultCommand(new MySpecialCommand());
 }
 void ArmSub::armDown() {
	 ArmSub::armMotor->Set(SmartDashboard::GetNumber("Arm pos 1", 0.0));
 }
 void ArmSub::stop() {
 	//ArmSub::armMotor->Set(0);
 }
 void ArmSub::armUp() {
	 ArmSub::armMotor->Set((SmartDashboard::GetNumber("Arm pos 2", 0.0)));
 }

 void ArmSub::readPos(){
	 SmartDashboard::PutNumber("Arm Position", armMotor->GetPosition());
 }

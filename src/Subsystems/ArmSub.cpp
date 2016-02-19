#include "ArmSub.h"
#include "../RobotMap.h"

 ArmSub::ArmSub() : Subsystem("Arm") {
 	armMotor = RobotMap::armMotor;

 	armMotor->SetControlMode(CANSpeedController::kPosition);
 	armMotor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
 	armMotor->SetP(0.8);
 	armMotor->SetI(0.0);
 	armMotor->SetD(0.05);
    armMotor->SetF(0.0);
 	armMotor->Enable();
 }

 void ArmSub::InitDefaultCommand() {
     // Set the default command for a subsystem here.
     // SetDefaultCommand(new MySpecialCommand());
 }
 void ArmSub::armDown() {
	 double Position = ArmSub::armMotor->GetPosition();
	 Position -= 0.5;
	 ArmSub::armMotor->Set(Position);
 }
 void ArmSub::stop() {
 	//ArmSub::armMotor->Set(0);
 }
 void ArmSub::armUp() {
	 double Position = ArmSub::armMotor->GetPosition();
	 Position += 0.5;
	 ArmSub::armMotor->Set(Position);
 }

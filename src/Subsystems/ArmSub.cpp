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
 
 //sets the arm motor to full speed reverse
 void ArmSub::armDown() {
	 double Position = ArmSub::armMotor->GetPosition();
	 Position -= 50;	 ArmSub::armMotor->Set(Position);
 	ArmSub::armMotor->Set(Position);
 }
 
 //stops the arm motor
 void ArmSub::stop() {
 	//stop collaborate and listen
 	//ArmSub::armMotor->Set(0);
 }
 //sets the arm motor to full speed forward
 void ArmSub::armUp() {
	//Everybody put your hands up!
	double Position = ArmSub::armMotor->GetPosition();
	Position += 50;
	ArmSub::armMotor->Set(Position);
}

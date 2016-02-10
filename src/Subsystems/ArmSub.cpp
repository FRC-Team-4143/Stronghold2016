#include "ArmSub.h"
#include "../RobotMap.h"

 ArmSub::ArmSub() : Subsystem("Arm") {
 	armMotor = RobotMap::armMotor;
 }

 void ArmSub::InitDefaultCommand() {
     // Set the default command for a subsystem here.
     // SetDefaultCommand(new MySpecialCommand());
 }
 void ArmSub::armDown() {
	 //move it on dowwwwnnnnn
 	ArmSub::armMotor->Set(-1);
 }
 void ArmSub::stop() {
	 //stop collaborate and listen
 	ArmSub::armMotor->Set(0);
 }
 void ArmSub::armUp() {
	//Everybody put your hands up!
 	ArmSub::armMotor->Set(1);
 }

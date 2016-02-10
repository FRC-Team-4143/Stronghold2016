#include "ArmSub.h"
#include "../RobotMap.h"

 ArmSub::ArmSub() : Subsystem("Arm") {
 	armMotor = RobotMap::armMotor;
 }

 void ArmSub::InitDefaultCommand() {
     // Set the default command for a subsystem here.
     // SetDefaultCommand(new MySpecialCommand());
 }
 //sets the arm motor to full speed reverse
 void ArmSub::armDown() {
 	ArmSub::armMotor->Set(-1);
 }
 //stops the arm motor
 void ArmSub::stop() {
 	ArmSub::armMotor->Set(0);
 }
 //sets the arm motor to full speed forward
 void ArmSub::armUp() {
 	ArmSub::armMotor->Set(1);
 }

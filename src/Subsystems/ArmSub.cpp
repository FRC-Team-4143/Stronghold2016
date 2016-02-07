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
 	ArmSub::armMotor->Set(-1);
 }
 void ArmSub::stop() {
 	ArmSub::armMotor->Set(0);
 }
 void ArmSub::armUp() {
 	ArmSub::armMotor->Set(1);
 }

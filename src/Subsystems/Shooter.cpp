#include "Shooter.h"
#include "../RobotMap.h"
#include "CANTalon.h"

Shooter::Shooter() : Subsystem("Shooter") {
	leftFront = RobotMap::leftFront;
	rightRear = RobotMap::rightRear;
	rightFront = RobotMap::rightFront;
	leftRear = RobotMap::leftRear;

	leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	leftFront->SetControlMode(CANSpeedController::kSpeed);
	leftFront->Set(-1);
	rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	rightFront->SetControlMode(CANSpeedController::kSpeed);
	rightFront->Set(-1);

	feeder = RobotMap::feeder;
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}
void Shooter::shootFront() {
	Shooter::leftFront->Enable();
	Shooter::leftFront->Enable();
}

void Shooter::shootBack(){
	Shooter::leftRear->Set(-1);
	Shooter::rightRear->Set(-1);
}

void Shooter::stopFront() {
	Shooter::leftFront->Disable();
	Shooter::rightFront->Disable();
}

void Shooter::stopBack(){
	Shooter::rightRear->Set(0);
	Shooter::leftRear->Set(0);
}

void Shooter::feed() {
	Shooter::feeder->Set(1);
}

void Shooter::stopFeed(){
	Shooter::feeder->Set(0);
}

#include "Shooter.h"
#include "../RobotMap.h"
#include "CANTalon.h"

Shooter::Shooter() : Subsystem("Shooter") {
	leftFront = RobotMap::leftFront;
	rightRear = RobotMap::rightRear;
	rightFront = RobotMap::rightFront;
	leftRear = RobotMap::leftRear;
/*
	leftFront->SetControlMode(CANSpeedController::kSpeed);
	leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	leftFront->SetP(0.8);
	leftFront->SetI(0.0);
	leftFront->SetD(0.05);
	leftFront->SetF(0.0);
	leftFront->Enable();

	rightFront->SetControlMode(CANSpeedController::kSpeed);
	rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	rightFront->SetP(0.8);
	rightFront->SetI(0.0);
	rightFront->SetD(0.05);
	rightFront->SetF(0.0);
	rightFront->Enable();
*/
	feeder = RobotMap::feeder;
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}
void Shooter::shootFront() {
	LOG("shootFront() called");
	leftFront->Set(1);//8
	rightFront->Set(-1);//8
}

void Shooter::shootBack(){
	LOG("shootBack() called");
	leftRear->Set(-1);
	rightRear->Set(1);
}

void Shooter::stopFront() {
	LOG("stopFront() called");
	leftFront->Set(0);
	rightFront->Set(0);
}

void Shooter::stopBack(){
	LOG("stopBack() called");
	rightRear->Set(0);
	leftRear->Set(0);
}

void Shooter::feed() {
	LOG("feed() called");
	feeder->Set(-1);
}

void Shooter::stopFeed(){
	LOG("stopfeed() called");
	feeder->Set(0);
}

double Shooter::getVelocity(){
	LOG("getVelocity() called");
	return leftFront->GetSpeed();
}

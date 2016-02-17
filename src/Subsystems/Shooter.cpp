#include "Shooter.h"
#include "../RobotMap.h"
#include "CANTalon.h"

Shooter::Shooter() : Subsystem("Shooter") {
	//Shooter is a shooter. Who knew?
	leftFront = RobotMap::leftFront;
	rightRear = RobotMap::rightRear;
	rightFront = RobotMap::rightFront;
	leftRear = RobotMap::leftRear;
/*
	leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	leftFront->SetControlMode(CANSpeedController::kSpeed);
	leftFront->SetP(0.8);
	leftFront->SetI(0.0);
	leftFront->SetD(0.05);
	leftFront->SetF(0.0);
	leftFront->Enable();

	rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	rightFront->SetControlMode(CANSpeedController::kSpeed);
	rightFront->SetP(0.8);
	rightFront->SetI(0.0);
	rightFront->SetD(0.05);
	rightFront->SetF(0.0);
	rightFront->Enable();
*/
	feeder = RobotMap::feeder;

	timer = new Timer();
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}
void Shooter::shootFront() {
	leftFront->Set(1);//8
	rightFront->Set(-1);//8
}

void Shooter::shootBack(){
	leftRear->Set(-1);
	rightRear->Set(1);
}

void Shooter::stopFront() {
	leftFront->Set(0);
	rightFront->Set(0);
}

void Shooter::stopBack(){
	rightRear->Set(0);
	leftRear->Set(0);
}

void Shooter::feed() {
	//Set feeder to full speed
	feeder->Set(-1);
}
void Shooter::stopFeed(){
	//Stop feeder
	feeder->Set(0);
}

double Shooter::getVelocity(){
	return leftFront->GetSpeed();
}

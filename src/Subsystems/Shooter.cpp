#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	leftFront = RobotMap::leftFront;
	rightRear = RobotMap::rightRear;
	rightFront = RobotMap::rightFront;
	leftRear = RobotMap::leftRear;

	feeder = RobotMap::feeder;
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}
void Shooter::shoot() {
	//Sets all motors' speeds to full
	Shooter::leftFront->Set(-1);
	Shooter::rightFront->Set(-1);
	Shooter::leftRear->Set(-1);
	Shooter::rightRear->Set(-1);
}
void Shooter::stop() {

	//Stops all motors' speeds
	Shooter::leftFront->Set(0);
	Shooter::rightRear->Set(0);
	Shooter::rightFront->Set(0);
	Shooter::leftRear->Set(0);
}
void Shooter::feed() {

	//Set feeder to full speed
	Shooter::feeder->Set(1);
}

void Shooter::stopFeed(){

	//Stop feeder
	Shooter::feeder->Set(0);
}

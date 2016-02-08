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
	Shooter::leftFront->Set(-1);
	Shooter::rightFront->Set(-1);
	Shooter::leftRear->Set(-1);
	Shooter::rightRear->Set(-1);
}
void Shooter::stop() {
	Shooter::leftFront->Set(0);
	Shooter::rightRear->Set(0);
	Shooter::rightFront->Set(0);
	Shooter::leftRear->Set(0);
}
void Shooter::feed() {
	Shooter::feeder->Set(1);
}

void Shooter::stopFeed(){
	Shooter::feeder->Set(0);
}

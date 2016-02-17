#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	//Shooter is a shooter. Who knew?
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
	//shoot all dem boulders
	Shooter::leftFront->Set(-1);
	Shooter::rightFront->Set(-1);
	Shooter::leftRear->Set(-1);
	Shooter::rightRear->Set(-1);
}
void Shooter::stop() {
	//stop all dem motors
	Shooter::leftFront->Set(0);
	Shooter::rightRear->Set(0);
	Shooter::rightFront->Set(0);
	Shooter::leftRear->Set(0);
}
void Shooter::feed() {
	//need all dem boulders
	Shooter::feeder->Set(1);
}
void Shooter::stopFeed(){
	//don't need those boulders
	Shooter::feeder->Set(0);
}

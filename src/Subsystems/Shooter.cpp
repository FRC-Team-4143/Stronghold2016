#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	//Shooter is a shooter. Who knew?
	leftFront = RobotMap::leftFront;
	rightRear = RobotMap::rightRear;
	rightFront = RobotMap::rightFront;
	leftRear = RobotMap::leftRear;

	leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	leftFront->SetControlMode(CANSpeedController::kPosition);
	rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	rightFront->SetControlMode(CANSpeedController::kPosition);


	feeder = RobotMap::feeder;

	timer = new Timer();
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
}
void Shooter::shoot() {
	//Sets all motors' speeds to full
	timer->Start();

	double dist = 34.5*timer->Get();

	Shooter::leftFront->Set(-dist);
	Shooter::rightFront->Set(-dist);
	Shooter::leftRear->Set(-1);
	Shooter::rightRear->Set(-1);
}
void Shooter::stop() {

	//Stops all motors' speeds
	Shooter::leftFront->SetPosition(0);
	Shooter::rightFront->SetPosition(0);

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

double Shooter::getPos(CANTalon* motor){

	return motor->GetPosition();
}

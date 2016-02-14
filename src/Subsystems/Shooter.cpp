#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	leftFront = RobotMap::leftFront;
	rightRear = RobotMap::rightRear;
	rightFront = RobotMap::rightFront;
	leftRear = RobotMap::leftRear;

	leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	leftFront->SetControlMode(CANSpeedController::kPosition);
	rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	rightFront->SetControlMode(CANSpeedController::kPosition);

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

	timer->Reset();
	timer->Start();

	double dist = 34.5*timer->Get();
	Shooter::leftFront->Set(-dist);
	Shooter::rightFront->Set(-dist);

	timer->Stop();
}
void Shooter::stop() {
	Shooter::leftFront->SetPosition(0);
	Shooter::rightFront->SetPosition(0);

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

double Shooter::getPos(CANTalon* motor){
	return motor->GetPosition();
}

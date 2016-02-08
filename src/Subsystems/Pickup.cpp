#include "Pickup.h"
#include "../RobotMap.h"

Pickup::Pickup() : Subsystem("Pickup") {
	solenoid = RobotMap::pickupSolenoid;
	compressor = RobotMap::compressor;
}

void Pickup::InitDefaultCommand() {

}

void Pickup::PushOut() {
	solenoid->Set(DoubleSolenoid::Value::kForward);
}

void Pickup::PushIn() {
	solenoid->Set(DoubleSolenoid::Value::kReverse);
}
void Pickup::PushStop() {
	solenoid->Set(DoubleSolenoid::Value::kOff);
}

void Pickup::GetAir(){
	compressor->Start();
}

void Pickup::StopAir(){
	compressor->Stop();
}

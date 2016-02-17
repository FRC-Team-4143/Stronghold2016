#include "Pickup.h"
#include "../RobotMap.h"
//Pickup methodddddddddddddddddddddddddddddddddddddd
Pickup::Pickup() : Subsystem("Pickup") {
	solenoid = RobotMap::pickupSolenoid;
	compressor = RobotMap::compressor;
}

void Pickup::InitDefaultCommand() {

}
//both pneumatic cylinders out
void Pickup::PushOut() {
	solenoid->Set(DoubleSolenoid::Value::kForward);
}
//both pneumatic cylinders in
void Pickup::PushIn() {
	solenoid->Set(DoubleSolenoid::Value::kReverse);
}

//stop pneumatic cylinders
void Pickup::PushStop() {
	solenoid->Set(DoubleSolenoid::Value::kOff);
}
//start compressor
void Pickup::GetAir(){
	compressor->Start();
}
//stop compressor
void Pickup::StopAir(){
	compressor->Stop();
}

#ifndef PICKUP_H
#define PICKUP_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Pickup: public Subsystem {

private:
	DoubleSolenoid* solenoid;
	Compressor* compressor;
public:
	Pickup();
	void PushIn();
	void PushOut();
	void PushStop();
	void RotateIn();
	void RotateOut();
	void PStop();
	void InitDefaultCommand();
	void GetAir();
	void StopAir();

};

#endif

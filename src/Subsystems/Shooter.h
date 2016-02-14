#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Timer.h"

class Shooter: public Subsystem {
private:
	CANTalon* leftFront;
	CANTalon* rightRear;
	CANTalon* rightFront;
	CANTalon* leftRear;

	Timer* timer;

	SpeedController* feeder;
public:
	Shooter();
	void InitDefaultCommand();
	void shootFront();
	void shootBack();
	void stopFront();
	void stopBack();
	void feed();
	void stopFeed();
	double getVelocity();
};

#endif

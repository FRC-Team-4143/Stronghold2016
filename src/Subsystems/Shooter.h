#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Timer.h"

class Shooter: public Subsystem {
private:
	 CANTalon* leftFront;
	 SpeedController* rightRear;
	 CANTalon* rightFront;
	 SpeedController* leftRear;

	SpeedController* feeder;

	Timer* timer;
public:
	Shooter();
	void InitDefaultCommand();
	void shoot();
	void stop();
	void feed();
	void stopFeed();
	double getPos(CANTalon* motor);
};

#endif

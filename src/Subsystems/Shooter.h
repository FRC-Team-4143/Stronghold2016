#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem {
private:
	SpeedController* leftFront;
	SpeedController* rightRear;
	SpeedController* rightFront;
	SpeedController* leftRear;

	SpeedController* feeder;
public:
	Shooter();
	void InitDefaultCommand();
	void shoot();
	void stop();
	void feed();
	void stopFeed();
};

#endif

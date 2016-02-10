#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem {
private:
	SpeedController* leftFront; //left front shooter motor
	SpeedController* rightRear; //right rear shooter motor
	SpeedController* rightFront; //right front shooter motor
	SpeedController* leftRear; //left rear shooter motor

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

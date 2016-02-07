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
public:
	Shooter();
	void InitDefaultCommand();
	void shoot();
	void stop();
	void pickup();
};

#endif

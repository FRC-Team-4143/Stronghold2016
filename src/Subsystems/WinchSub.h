#ifndef WinchSub_H
#define WinchSub_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class WinchSub: public Subsystem
{
private:
	CANTalon* motor;
	AnalogInput* shooterSensor;
	PIDController* shooter;
public:
	bool shooterRaised;

	WinchSub();
	void InitDefaultCommand();
	void setPos(double pos);
	void readPos();
	void disablePositionControl();
	void reset();
};

#endif

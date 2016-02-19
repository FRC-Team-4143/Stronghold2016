#ifndef WinchSub_H
#define WinchSub_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class WinchSub: public Subsystem
{
private:
	CANTalon* motor;

public:
	WinchSub();
	void InitDefaultCommand();
	void setPos(double pos);
	void readPos();
	void disablePositionControl();
};

#endif

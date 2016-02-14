#ifndef ARM_H
#define ARM_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ArmSub: public Subsystem {
private:
	CANTalon* armMotor;

public:
	ArmSub();
	void InitDefaultCommand();
	void armDown();
	void stop();
	void armUp();
};

#endif

#ifndef ARM_H
#define ARM_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ArmSub: public Subsystem {
private:
	SpeedController* armMotor;

public:
	ArmSub();
	void InitDefaultCommand();
	void armDown();
	void stop();
	void armUp();
};

#endif

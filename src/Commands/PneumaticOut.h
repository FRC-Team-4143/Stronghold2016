#ifndef PneumaticOut_H
#define PneumaticOut_H

#include "WPILib.h"

class PneumaticOut: public Command
{
public:
	PneumaticOut();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

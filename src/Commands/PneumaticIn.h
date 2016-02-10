#ifndef PneumaticIn_H
#define PneumaticIn_H

#include "WPILib.h"

class PneumaticIn: public Command
{

public:
	PneumaticIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

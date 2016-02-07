#ifndef ARMDOWN_H
#define ARMDOWN_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class ArmDown: public Command {
public:
	ArmDown();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif

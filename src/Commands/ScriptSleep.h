#ifndef SCRIPTSLEEP_H
#define SCRIPTSLEEP_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptSleep: public Command
{
public:
	ScriptSleep(const char* name, float seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float _seconds;
};

#endif

#ifndef SCRIPTDRIVE_H
#define SCRIPTDRIVE_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptDrive: public Command
{
public:
	ScriptDrive(const char* name, float x, float y, float z, float seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float _x;
	float _y;
	float _z;
	float _seconds;
};

#endif

#ifndef SCRIPTCAMDRIVE_H
#define SCRIPTCAMDRIVE_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptCamDrive: public Command
{
public:
	ScriptCamDrive(const char* name, double x, double y, double maxspeed, double seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double _x;
	double _y;
	double _maxspeed;
	double _seconds;
	double _angle;
	double _offset;
	double _p;
	double _tol;
	double _center;
	int    _time;
};

#endif

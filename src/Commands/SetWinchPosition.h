#ifndef SetWinchPosition_H
#define SetWinchPosition_H

#include "WPILib.h"

class SetWinchPosition: public Command
{
private:
	double pos;
public:
	SetWinchPosition(double pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

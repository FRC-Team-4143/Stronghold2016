#ifndef SetWinchPosition_H
#define SetWinchPosition_H

#include "WPILib.h"

class SetWinchPosition: public Command
{
private:
	double pos;
	bool disable;
public:
	SetWinchPosition(double pos, bool disable);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef Shoot_H
#define Shoot_H

#include "WPILib.h"

class Shoot: public Command
{
private:
	bool stop;
	double speed;
public:
	Shoot(bool stop, double time, double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

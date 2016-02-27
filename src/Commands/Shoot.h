#ifndef Shoot_H
#define Shoot_H

#include "WPILib.h"

class Shoot: public Command
{
private:
	bool stop;
public:
	Shoot(bool stop);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
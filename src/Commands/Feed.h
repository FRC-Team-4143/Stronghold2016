#ifndef FEED_H
#define FEED_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class Feed: public Command {
public:
	Feed();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif

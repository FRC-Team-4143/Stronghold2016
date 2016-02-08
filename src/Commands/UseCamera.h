#ifndef UseCamera_H
#define UseCamera_H

#include "WPILib.h"

class UseCamera: public Command
{
public:
	UseCamera();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

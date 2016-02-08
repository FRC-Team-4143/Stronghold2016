#ifndef ResetSteeringEncoders_H
#define ResetSteeringEncoders_H

#include "WPILib.h"

class ResetSteeringEncoders: public Command
{
public:
	ResetSteeringEncoders();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

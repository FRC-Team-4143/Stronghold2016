#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick* driverJoystick;
public:
	OI();
	float GetRightTrigger();
	float GetLeftTrigger();
	float GetJoystickX();
	float GetJoystickY();
	float GetJoystickZ();
	bool GetButtonStart();

	Command* armUp;
	Command* armDown;
	Command* stowArm;
	Command* useCamera;
	Command* unwindWheels;
	Command* turnFrontRightSteer;
	Command* turnFrontLeftSteer;
	Command* turnRearRightSteer;
	Command* turnRearLeftSteer;
	Command* winchSet1;
	Command* winchSet2;
	Command* winchSet3;
	Command* resetWinch;
	Command* deFeed;
	Command* arcade;

	Joystick* GetDriverJoystick() { return driverJoystick; }
};

#endif

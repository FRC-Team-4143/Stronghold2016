#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick* driverJoystick;
	Joystick* pickerJoystick;
public:
	OI();
	float GetJoystickX();
	float GetJoystickY();
	float GetJoystickZ();
	bool GetButtonStart();

	Command* shoot;
	Command* feed;
	Command* armUp;
	Command* armDown;
	Command* useCamera;
	Command* pneumaticIn;
	Command* pneumaticOut;
	Command* unwindWheels;
	Command* turnFrontRightSteer;
	Command* turnFrontLeftSteer;
	Command* turnRearRightSteer;
	Command* turnRearLeftSteer;

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

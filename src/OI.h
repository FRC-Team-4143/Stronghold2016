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

	Command* shoot; //command for shooting
	Command* prepareShoot;
	Command* armUp; //command for raising arm
	Command* armDown; //command for lowering arm
	Command* useCamera; //command for using camera
	Command* pneumaticIn; //command for pulling pneumatics in
	Command* pneumaticOut; //command for pushing pneumatics out
	Command* unwindWheels;
	Command* turnFrontRightSteer;
	Command* turnFrontLeftSteer;
	Command* turnRearRightSteer;
	Command* turnRearLeftSteer;

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

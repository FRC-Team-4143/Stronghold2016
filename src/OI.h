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

	Command* shoot;
	Command* pickup;
	Command* armUp;
	Command* armDown;

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

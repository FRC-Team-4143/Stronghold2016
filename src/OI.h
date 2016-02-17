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
	Command* feed; //command for feeding
	Command* armUp; //command for raising arm
	Command* armDown; //command for lowering arm
	Command* useCamera; //command for using camera
	Command* pneumaticIn; //command for pulling pneumatics in
	Command* pneumaticOut; //command for pushing pneumatics out
	Command* unwindWheels;

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

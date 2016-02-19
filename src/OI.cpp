#include <Commands/SetWheelOffsets.h>
#include "OI.h"

#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/ArmUp.h"
#include "Commands/ArmDown.h"
#include "Commands/UseCamera.h"
#include "Commands/UnwindWheels.h"
#include "Commands/RunMotor.h"
#include "Commands/SetWheelOffsets.h"

const uint32_t JOYSTICK_LX_AXIS    = 0;
const uint32_t JOYSTICK_LY_AXIS    = 1;
const uint32_t JOYSTICK_LTRIG_AXIS = 2;
const uint32_t JOYSTICK_RTRIG_AXIS = 3;
const uint32_t JOYSTICK_RX_AXIS    = 4;
const uint32_t JOYSTICK_RY_AXIS    = 5;

const uint32_t JOYSTICK_BUTTON_A     = 1;
const uint32_t JOYSTICK_BUTTON_B     = 2;
const uint32_t JOYSTICK_BUTTON_X     = 3;
const uint32_t JOYSTICK_BUTTON_Y     = 4;
const uint32_t JOYSTICK_BUTTON_LB    = 5;
const uint32_t JOYSTICK_BUTTON_RB    = 6;
const uint32_t JOYSTICK_BUTTON_BACK  = 7;
const uint32_t JOYSTICK_BUTTON_START = 8;
const uint32_t JOYSTICK_BUTTON_LEFT  = 9;
const uint32_t JOYSTICK_BUTTON_RIGHT = 10;
const float JOYSTICK_DEAD_ZONE = 0.1;

OI::OI() {
	driverJoystick = new Joystick(0);
	armUp = new ArmUp();
	armDown = new ArmDown();
	useCamera = new UseCamera();
	unwindWheels = new UnwindWheels();
	turnFrontRightSteer = new RunMotor(RobotMap::driveTrainFrontRightSteer);
	turnFrontLeftSteer = new RunMotor(RobotMap::driveTrainFrontLeftSteer);
	turnRearRightSteer = new RunMotor(RobotMap::driveTrainRearRightSteer);
	turnRearLeftSteer = new RunMotor(RobotMap::driveTrainRearLeftSteer);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_Y))->WhileHeld(armUp);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_A))->WhileHeld(armDown);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_BACK))->WhileHeld(unwindWheels);

    SmartDashboard::PutData("Camera", useCamera);
    SmartDashboard::PutData("SetWheelOffsets", new SetWheelOffsets());

    SmartDashboard::PutData("Turn Front Left Steering Motor", turnFrontLeftSteer);
    SmartDashboard::PutData("Turn Front Right Steering Motor", turnFrontRightSteer);
    SmartDashboard::PutData("Turn Rear Left Steering Motor", turnRearLeftSteer);
    SmartDashboard::PutData("Turn Rear Right Steering Motor", turnRearRightSteer);
}

float OI::GetRightTrigger() {
	auto value = driverJoystick->GetRawAxis(JOYSTICK_RTRIG_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetLeftTrigger() {
	auto value = driverJoystick->GetRawAxis(JOYSTICK_LTRIG_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickX() {
	auto value = driverJoystick->GetRawAxis(JOYSTICK_LX_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickY() {
	auto value =driverJoystick->GetRawAxis(JOYSTICK_LY_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickZ() {
	auto value = driverJoystick->GetRawAxis(JOYSTICK_RX_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

bool OI::GetButtonStart(){
	auto value = GetDriverJoystick()->GetRawButton(JOYSTICK_BUTTON_START);
	return (value);
}

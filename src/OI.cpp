#include <Commands/Feed.h>
#include "OI.h"

#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/Shoot.h"
#include "Commands/PrepareShoot.h"
#include "Commands/ArmUp.h"
#include "Commands/ArmDown.h"
#include "Commands/UseCamera.h"
#include "Commands/ResetSteeringEncoders.h"
#include "Commands/PneumaticIn.h"
#include "Commands/PneumaticOut.h"
#include "Commands/UnwindWheels.h"
#include "Commands/RunMotor.h"

//We need all of the buttons!!!!!!!!!!!

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
	shoot = new Shoot();
	prepareShoot = new PrepareShoot();
	feed = new Feed();
	armUp = new ArmUp();
	armDown = new ArmDown();
	useCamera = new UseCamera();
	pneumaticIn = new PneumaticIn();
	pneumaticOut = new PneumaticOut();
	unwindWheels = new UnwindWheels();
	turnFrontRightSteer = new RunMotor(RobotMap::driveTrainFrontRightSteer);
	turnFrontLeftSteer = new RunMotor(RobotMap::driveTrainFrontLeftSteer);
	turnRearRightSteer = new RunMotor(RobotMap::driveTrainRearRightSteer);
	turnRearLeftSteer = new RunMotor(RobotMap::driveTrainRearLeftSteer);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhileHeld(shoot); //sets right bumper to shoot
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhileHeld(prepareShoot);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_START))->WhileHeld(feed);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_START))->WhenPressed(useCamera); //sets Start button to start camera
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_X))->WhileHeld(pneumaticIn); //sets X button to pull pneumatics in


	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_BACK))->WhileHeld(unwindWheels);

    SmartDashboard::PutData("Camera", useCamera);
    SmartDashboard::PutData("Reset Steering Encoders", new ResetSteeringEncoders());

    SmartDashboard::PutData("Turn Front Left Steering Motor", turnFrontLeftSteer);
    SmartDashboard::PutData("Turn Front Right Steering Motor", turnFrontRightSteer);
    SmartDashboard::PutData("Turn Rear Left Steering Motor", turnRearLeftSteer);
    SmartDashboard::PutData("Turn Rear Right Steering Motor", turnRearRightSteer);
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

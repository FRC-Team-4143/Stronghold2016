#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "OI.h"
#include "LiveWindow/LiveWindow.h"
#include "Subsystems/GyroSub.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/ArmSub.h"
#include "Subsystems/BasicCameraSub.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/CameraSub.h"
#include "Subsystems/WinchSub.h"
#include "Commands/AutonomousCommand.h"

class Robot : public IterativeRobot {
public:
	Command* autonomousCommand;
	static OI* oi;
	static DriveTrain* driveTrain;
	static ArmSub* armSub;
	static GyroSub* gyroSub;
	static Shooter* shooter;
	static CameraSub* cameraSub;
	static std::shared_ptr<BasicCameraSub> basicCameraSub;
	static WinchSub* winchSub;
	LiveWindow *lw = LiveWindow::GetInstance();

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	void cameraInit();
};
#endif

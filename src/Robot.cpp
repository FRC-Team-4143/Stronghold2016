#include "Robot.h"

OI* Robot::oi;
Shooter* Robot::shooter;
ArmSub* Robot::armSub;
GyroSub* Robot::gyroSub = nullptr;
DriveTrain* Robot::driveTrain = nullptr;

void Robot::RobotInit() {

	RobotMap::init();
	gyroSub = new GyroSub();
	driveTrain = new DriveTrain();
    shooter = new Shooter();
    armSub = new ArmSub();
	oi = new OI();

	autonomousCommand = new AutonomousCommand();
  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();

	driveTrain->SetWheelbase(24, 21.5, 24);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);


#include "Robot.h"
#include "Commands/DriveDistance.h"
#include "Modules/Logger.h"
//declare all of the pointers!!!!!!!
OI* Robot::oi;
Shooter* Robot::shooter = nullptr;
ArmSub* Robot::armSub = nullptr;
GyroSub* Robot::gyroSub = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
CameraSub* Robot::cameraSub = nullptr;
Pickup* Robot::pickup = nullptr;

void Robot::RobotInit() {

	RobotMap::init();
	gyroSub = new GyroSub();
	driveTrain = new DriveTrain();
    shooter = new Shooter();
    armSub = new ArmSub();
    cameraSub = new CameraSub();
    pickup = new Pickup();
	oi = new OI();

	driveTrain->SetWheelbase(24, 21.5, 24);

	driveTrain->frontLeft->Enable();
	driveTrain->frontRight->Enable();
	driveTrain->rearLeft->Enable();
	driveTrain->rearRight->Enable();

	autonomousCommand = new DriveDistance(0.5, 0, 0, 5);
  }

void Robot::DisabledInit(){
/*Does an'tony even read all of the comments? I should leave a message.
 * Potato
 * Potato
 * */
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


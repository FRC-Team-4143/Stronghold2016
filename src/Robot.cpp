#include "Robot.h"
#include "Commands/DriveDistance.h"
#include "Modules/Logger.h"
#include "Commands/ScriptDrive.h"
#include "Modules/CommandListParser.h"
#include "Commands/ScriptSleep.h"
#include "Commands/ShootCycle.h"
#include "Commands/ScriptCommand.h"
#include "Commands/ScriptArm.h"
#include "Commands/SetWinchPosition.h"
#include "Commands/ScriptGyroDrive.h"
#include "Commands/ScriptCamDrive.h"
#include "Commands/ZeroYaw.h"
#include "Commands/Feed.h"
#include "Commands/ScriptFieldCentricCrab.h"
#include "Commands/WaitForVision.h"
#include "Commands/BackupToCenter.h"
#include "Commands/DriveTilVision.h"

OI* Robot::oi;
Shooter* Robot::shooter = nullptr;
ArmSub* Robot::armSub = nullptr;
GyroSub* Robot::gyroSub = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
std::shared_ptr<BasicCameraSub> Robot::basicCameraSub;
WinchSub* Robot::winchSub = nullptr;
VisionBridgeSub* Robot::visionBridge = nullptr;

void Robot::RobotInit() {

	Preferences::GetInstance();
	RobotMap::init();

	ScriptInit();
	SmartDashboard::PutString("ScriptCommand", "S(0.5)");
	SmartDashboard::PutString("ScriptValid", "");

	SmartDashboard::PutNumber("vision center", 35.0);
	SmartDashboard::PutNumber("vision P", 0.1); //0.2
	SmartDashboard::PutNumber("vision I", .01); //0.005 Worked without speed control
	SmartDashboard::PutNumber("vision D", .022); //0.05
	SmartDashboard::PutNumber("vision tol", 10);
	SmartDashboard::PutNumber("long shot cutoff", 50);

	gyroSub = new GyroSub();
	driveTrain = new DriveTrain();
    shooter = new Shooter();
    armSub = new ArmSub();
    basicCameraSub.reset(new BasicCameraSub("cam0"));
    winchSub = new WinchSub();
	oi = new OI();
	visionBridge = new VisionBridgeSub();

	driveTrain->SetWheelbase(24, 21.5, 24);
	driveTrain->loadWheelOffsets();




  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
	//armSub->readPos();
	winchSub->readPos();
	driveTrain->updateDistanceEncoders();
	SmartDashboard::PutNumber("feeder sensor", RobotMap::feederSensor->GetAverageVoltage());
	SmartDashboard::PutBoolean("Shooter Raised", Robot::winchSub->shooterRaised);
	SmartDashboard::PutNumber("Gyro Yaw", RobotMap::imu->GetYaw());
	SmartDashboard::PutNumber("Vision Position", Robot::visionBridge->GetPosition());
	SmartDashboard::PutNumber("Vision Distance", Robot::visionBridge->GetDistance());
}

void Robot::AutonomousInit() {
	driveTrain->enableSteeringPID();

	RobotMap::imu->ZeroYaw();
	autonomousCommand = new ScriptCommand("ScriptCommand");
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	//armSub->readPos();
	winchSub->readPos();
	driveTrain->updateDistanceEncoders();
	SmartDashboard::PutNumber("feeder sensor", RobotMap::feederSensor->GetAverageVoltage());
	SmartDashboard::PutBoolean("Shooter Raised", Robot::winchSub->shooterRaised);
	SmartDashboard::PutNumber("Gyro Yaw", RobotMap::imu->GetYaw());
	SmartDashboard::PutNumber("Vision Position", Robot::visionBridge->GetPosition());
	SmartDashboard::PutNumber("Vision Distance", Robot::visionBridge->GetDistance());
}

void Robot::TeleopInit() {
	driveTrain->enableSteeringPID();
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	//armSub->readPos();
	winchSub->readPos();
	driveTrain->updateDistanceEncoders();
	SmartDashboard::PutNumber("feeder sensor", RobotMap::feederSensor->GetAverageVoltage());
	SmartDashboard::PutBoolean("Shooter Raised", Robot::winchSub->shooterRaised);
	SmartDashboard::PutNumber("Gyro Yaw", RobotMap::imu->GetYaw());
	SmartDashboard::PutNumber("Vision Position", Robot::visionBridge->GetPosition());
	SmartDashboard::PutNumber("Vision Distance", Robot::visionBridge->GetDistance());
}

void Robot::TestPeriodic() {
	lw->Run();
}

void Robot::ScriptInit() {
	std::cout << "Robot::ScriptInit" << std::endl;

	CommandListParser& parser(CommandListParser::GetInstance());

	parser.AddCommand(CommandParseInfo("Drive", { "D", "d" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto x = parameters[0];
		auto y = parameters[1];
		auto z = parameters[2];
		auto timeout = parameters[3];
		Command* command = new ScriptDrive("Drive", x, y, z, timeout);
		//if (0 == timeout) timeout = 4;
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("DriveTilVision", { "DV", "dv" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto y = parameters[0];
		auto x = parameters[1];
		auto z = parameters[2];
		auto timeout = parameters[3];
		Command* command = new DriveTilVision(y, x, z, timeout);
		//if (0 == timeout) timeout = 4;
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("WaitForVision", { "WAIT", "wait" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(0);
		Command* command = new WaitForVision();
		//if (0 == timeout) timeout = 4;
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("BackupToCenter", { "BACK", "back" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(0);
		Command* command = new BackupToCenter();
		//if (0 == timeout) timeout = 4;
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Shoot", { "SH", "sh" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(0);
		Command* command = new ShootCycle();
		//if (0 == timeout) timeout = 4;
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Sleep", { "S", "s" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(1);
		auto timeout = parameters[0];
		Command* command = new ScriptSleep("Sleep", timeout);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Arm", { "A", "a" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(1);
		auto pos = parameters[0];
		Command* command = new ScriptArm(pos);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Winch", { "W", "w" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(3);
		auto pos = parameters[0];
		auto holdPos = parameters[1];
		auto timeout = parameters[2];
		Command* command = new SetWinchPosition(pos, holdPos, timeout);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("DriveGyro", { "DG", "dg" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto x = parameters[0];
		auto y = parameters[1];
		auto desiredangle = parameters[2];
		auto timeout = parameters[3];
		Command* command = new ScriptGyroDrive("DriveGyro", x, y, desiredangle, timeout);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("DriveDistance", { "DD", "dd" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
			parameters.resize(4);
			auto x = parameters[0];
			auto y = parameters[1];
			auto twist = parameters[2];
			auto distance = parameters[3];
			Command* command = new DriveDistance(x, y, twist, distance);
			fCreateCommand(command, 0);
		}));

		parser.AddCommand(CommandParseInfo("DriveCam", { "DC", "dc" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
			parameters.resize(4);
			auto x = parameters[0];
			auto y = parameters[1];
			auto maxspeed = parameters[2];
			auto timeout = parameters[3];
			Command* command = new ScriptCamDrive("DriveCam", x, y, maxspeed, timeout);
			fCreateCommand(command, 0);
		}));

		parser.AddCommand(CommandParseInfo("Feed", { "F", "f" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
			parameters.resize(1);
			auto timeout = parameters[0];
			Command* command = new Feed(timeout);
			fCreateCommand(command, 0);
		}));

		parser.AddCommand(CommandParseInfo("FieldCentricDrive", { "FC", "fc" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
			parameters.resize(4);
			auto y = parameters[0];
			auto x = parameters[1];
			auto z = parameters[2];
			auto timeout = parameters[3];
			Command* command = new ScriptFieldCentricCrab(z, y, x, timeout);
			//if (0 == timeout) timeout = 4;
			fCreateCommand(command, 0);
		}));

	/*
	parser.AddCommand(CommandParseInfo("DriveMouse", { "DM", "dm" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto x = parameters[0];
		auto y = parameters[1];
		auto maxspeed = parameters[2];
		auto timeout = parameters[3];
		Command* command = new ScriptMouseDrive("DriveMouse", x, y, maxspeed, timeout);
		fCreateCommand(command, 0);
	}));



	parser.AddCommand(CommandParseInfo("DriveDisplacement", { "DD", "dd" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto deltaX = parameters[0];
		auto deltaY = parameters[1];
		auto maxspeed = parameters[2];
		auto timeoutSeconds = parameters[3];
		if (0 == timeoutSeconds) timeoutSeconds = 5;
		Command* command = new ScriptDisplacementDrive("DriveCam", deltaX, deltaY, maxspeed, timeoutSeconds);
		fCreateCommand(command, 0);
	}));


	parser.AddCommand(CommandParseInfo("Elevate", { "E", "e" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(2);
		auto axis = parameters[0];
		auto timeout = parameters[1];
		Command* command = new ScriptElevate("Elevate", axis, timeout);
		//if (0 == timeout) timeout = 4;
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("GyroReset", { "GR", "gr" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(0);
		Command* command = new ResetGyro();
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Mode", { "M", "m" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(1);
		auto mode = parameters[0];
		Command* command = new ScriptMode("Mode", mode);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("RotateBy", { "RB", "R", "rb", "r" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(2);
		auto angle = parameters[0];
		auto timeout = parameters[1];
		if (0 == timeout) timeout = 4;
		Command* command = new ScriptRotateBy("RotateBy", angle, timeout);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("RotateByX", { "RBX", "rbx" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(5);
		auto angle = parameters[0];
		auto timeout = parameters[1];
		auto stableTickThreshold = parameters[2];
		auto maxSpeed = parameters[3];
		auto p = parameters[4];
		if (0 == timeout) timeout = 4;
		Command* command = new ScriptRotateByX("RotateBy", angle, timeout, stableTickThreshold, maxSpeed, p);
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Raise1level", { "RL", "rl" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(0);
		Command* command = new Raise1Level();
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("Squeeze", { "SQ", "sq" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(0);
		Command* command = new ToggleSqueezeMode();
		fCreateCommand(command, 0);
	}));

	parser.AddCommand(CommandParseInfo("SetHeight", { "SH", "sh" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(2);
		auto height = parameters[0];
		auto timeout = parameters[1];
		Command* command = new SetHeight(height, timeout);
		fCreateCommand(command, 0);
	}));
*/
}

START_ROBOT_CLASS(Robot);


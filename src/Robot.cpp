#include "Robot.h"
#include "Commands/DriveDistance.h"
#include "Modules/Logger.h"
#include "Commands/ScriptDrive.h"
#include "Modules/CommandListParser.h"
#include "Commands/ScriptSleep.h"
#include "Commands/ShootCycle.h"
#include "Commands/ScriptCommand.h"

OI* Robot::oi;
Shooter* Robot::shooter = nullptr;
ArmSub* Robot::armSub = nullptr;
GyroSub* Robot::gyroSub = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
CameraSub* Robot::cameraSub = nullptr;
std::shared_ptr<BasicCameraSub> Robot::basicCameraSub;
WinchSub* Robot::winchSub = nullptr;
VisionBridgeSub* Robot::visionBridge = nullptr;

void Robot::RobotInit() {

	Preferences::GetInstance();
	RobotMap::init();

	ScriptInit();
	SmartDashboard::PutString("ScriptCommand", "S(0.5)");
	SmartDashboard::PutString("ScriptValid", "");

	gyroSub = new GyroSub();
	driveTrain = new DriveTrain();
    shooter = new Shooter();
    armSub = new ArmSub();
    //cameraSub = new CameraSub();
    basicCameraSub.reset(new BasicCameraSub("cam0"));
    winchSub = new WinchSub();
	oi = new OI();
	visionBridge = new VisionBridgeSub();

	driveTrain->SetWheelbase(24, 21.5, 24);
	driveTrain->loadWheelOffsets();

	driveTrain->frontLeft->Enable();
	driveTrain->frontRight->Enable();
	driveTrain->rearLeft->Enable();
	driveTrain->rearRight->Enable();


  }

void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	autonomousCommand = new ScriptCommand("ScriptCommand");
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

	parser.AddCommand(CommandParseInfo("Shoot", { "SH", "sh" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(1);
		auto timeout = parameters[0];
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

	parser.AddCommand(CommandParseInfo("DriveCam", { "DC", "dc" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto x = parameters[0];
		auto y = parameters[1];
		auto maxspeed = parameters[2];
		auto timeout = parameters[3];
		Command* command = new ScriptCamDrive("DriveCam", x, y, maxspeed, timeout);
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

	parser.AddCommand(CommandParseInfo("DriveGyro", { "DG", "dg" }, [](std::vector<float> parameters, std::function<void(Command*, float)> fCreateCommand) {
		parameters.resize(4);
		auto x = parameters[0];
		auto y = parameters[1];
		auto maxspeed = parameters[2];
		auto timeout = parameters[3];
		Command* command = new ScriptGyroDrive("DriveGyro", x, y, maxspeed, timeout);
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


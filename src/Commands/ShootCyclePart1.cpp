#include "ShootCyclePart1.h"
#include "SetWinchPosition.h"
#include "DefeedShoot.h"
#include "ScriptCamDrive.h"

ShootCyclePart1::ShootCyclePart1()
{

	AddParallel(new SetWinchPosition(3, true, 0));
	AddParallel(new DefeedShoot(2));
	AddSequential(new ScriptCamDrive("DriveCam", 0, 0, 0.35, 0));

	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
}

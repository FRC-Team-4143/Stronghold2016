#include "ShootCycle.h"
#include "SetWinchPosition.h"
#include "Shoot.h"
#include "Feed.h"
#include "DeFeed.h"
#include "DisableWinchControl.h"
#include "StopShoot.h"
#include "ScriptCamDrive.h"
#include "DefeedShoot.h"
#include "../Robot.h"
#include "ShootCyclePart1.h"
#include "PositionDrive.h"
#include "SetWheelsTwist.h"

ShootCycle::ShootCycle()
{

	AddSequential(new ShootCyclePart1());

	AddParallel(new Feed(2));
	AddSequential(new SetWheelsTwist(2));//ScriptCamDrive("DriveCam", 0, 0, 0.35, 1));

	AddParallel(new SetWinchPosition(2, false, 0));
	AddSequential(new StopShoot());




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

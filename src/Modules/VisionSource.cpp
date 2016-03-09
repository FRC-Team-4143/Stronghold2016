/*
 * VisionSource.cpp
 *
 *  Created on: Mar 8, 2016
 *      Author: Anthony
 */
#include <WPILib.h>
#include <Modules/VisionSource.h>
#include "../Robot.h"


VisionSource::VisionSource() {
	// TODO Auto-generated constructor stub

}

VisionSource::~VisionSource() {
	// TODO Auto-generated destructor stub
}

double VisionSource::PIDGet(){
	printf("vision source pid get \n");
	return Robot::visionBridge->GetPosition();

}

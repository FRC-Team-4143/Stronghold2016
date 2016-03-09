/*
 * VisionSink.cpp
 *
 *  Created on: Mar 8, 2016
 *      Author: Anthony
 */
#include <WPILib.h>
#include <Modules/VisionSink.h>


VisionSink::VisionSink() {
	// TODO Auto-generated constructor stub

}

VisionSink::~VisionSink() {
	// TODO Auto-generated destructor stub
}

void VisionSink::PIDWrite(float output){
	value = output;
}

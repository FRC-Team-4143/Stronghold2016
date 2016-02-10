#ifndef CameraSub_H
#define CameraSub_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CameraSub: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	CameraSub();
	void InitDefaultCommand();
	void StartCamera();
	void StopCamera();
	void ShowCamera();

	CameraServer* server;
	IMAQdxSession sessionCam0;
	Image *frameCam0;
	IMAQdxError imaqError;
	USBCamera cam0; //Camera object
};

#endif

#include "CameraSub.h"
#include "../RobotMap.h"
#include <USBCamera.h>

CameraSub::CameraSub() :
		Subsystem("Camera Subsystem")
, cam0("cam0", true)
{
	//initializes images
	frameCam0 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);;

	//instance of camera server
	server = CameraServer::GetInstance();

	//sets camera server quality
	server->SetQuality(50);

	//sets framerate
	cam0.SetFPS(5);

	//sets size
	cam0.SetSize(320, 240);

	cameraCurrent = 0;
}

void CameraSub::InitDefaultCommand()
{
	//SetDefaultCommand(new ShowCameraDefault());
}

void CameraSub::StartCamera(){
	IMAQdxConfigureAcquisition(sessionCam0, true, 100);
	cam0.OpenCamera();
	cam0.StartCapture();
}

void CameraSub::StopCamera(){
	cam0.StopCapture();
	cam0.CloseCamera();
}

void CameraSub::ShowCamera(){
	cam0.GetImage(frameCam0);
	server->SetImage(frameCam0);
}

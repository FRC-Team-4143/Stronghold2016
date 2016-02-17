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

	//sets frame rate
	cam0.SetFPS(5);

	//sets size
	cam0.SetSize(320, 240);

}

void CameraSub::InitDefaultCommand()
{
	//SetDefaultCommand(new ShowCameraDefault());
}

void CameraSub::StartCamera(){

	//Configuring properties for Camera
	IMAQdxConfigureAcquisition(sessionCam0, true, 100);

	//Starts connection with Camera
	cam0.OpenCamera();

	//Starts displaying image
	cam0.StartCapture();
}

void CameraSub::StopCamera(){

	//Stop displaying image
	cam0.StopCapture();

	//Stops connection with Camera
	cam0.CloseCamera();
}

void CameraSub::ShowCamera(){

	//Getting image from Camera
	cam0.GetImage(frameCam0);

	//Setting image from Camera
	server->SetImage(frameCam0);
}

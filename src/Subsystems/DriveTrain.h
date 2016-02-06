#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <WPILib.h>
#include <math.h>
#include "../AnalogChannelVolt.h"
#include "../Subsystems/GyroSub.h"
//#include "../Subsystems/MouseSubsystem.h"

class DriveTrain: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	
	static constexpr double pi=3.14159;
		
	bool unwinding;
	
	//Steering Functions
	void LeftTurn4Wheels();	//Calculates a left hand turn
	void RightTurn4Wheels();	//Calculates a right hand turn
	
	//DriveDirection
	bool driveFront;
	
	//Steering Variables	
	double radian; // input steering angle in radians
	double A;	//A is the ratio of X to turn harder 
	double W;	//W is the distance form the mid-point of one back wheel to the mid-point of the other back wheel
	double X;	//X is the distance form the mid-point of the back wheels to the mid-point of the front wheels 
	double Y;	//Y is the distance from the mid-point of one front wheel to the mid-point of the other front wheel
	
	double FL;	//FL, distance from Front Left Wheel to the center of rotation
	double FR;	//FR, distance from Front Right Wheel to the center of rotation
	double RL;	//RL, distance from Rear Left Wheel to the center of rotation
	double RR;	//RR, distance from Rear Right Wheel to the center of rotation
	
	double Z;	//Z, distance form A * X to center of rotation
	
	double thetaRC;	//Angle used to calculate all other angles
	
	double thetaFL;	//thetaFL, angle from Front Left Wheel to the center of rotation
	double thetaFR;	//thetaFR, angle from Front Right Wheel to the center of rotation
	double thetaRL;	//thetaRL, angle from Rear Left Wheel to the center of rotation
	double thetaRR;	//thetaRR, angle from Rear Right Wheel to the center of rotation
	double FRRatio;	//Ratio of Speed of Front Right wheel
	double FLRatio;	//Ratio of Speed of Front Left wheel
	double RRRatio;	//Ratio of Speed of Rear Right wheel
	double RLRatio;	//Ratio of Speed of Rear Left wheel

	double FLOffset;
	double FROffset;
	double RLOffset;
	double RROffset;

	//Crab & Pivot Variables
	double position; //Input position for crab
	double AP;
	double BP;
	double CP;
	double DP;

	//Inversion Variabls
	int FLInv;
	int FRInv;
	int RLInv;
	int RRInv;

	//Pivot Variables
	double radius; //distance from center to each wheel
	double velocity; //robot speed
	double angularvelocity; //input from OI
	double robotangle; //current robot angle from Gyro
	double inverserobotangle; //2pi-robotangle

	//Wheel position in angle relative to robot
	double FLWP;
	double FRWP;
	double RLWP;
	double RRWP;

	//Wheel velocities in X direction
	double FLXVel;
	double FRXVel;
	double RLXVel;
	double RRXVel;

	//Wheel velocities in Y direction
	double FLYVel;
	double FRYVel;
	double RLYVel;
	double RRYVel;

	//
	double FLPos;
	double FRPos;
	double RRPos;
	double RLPos;

	//Wheel velocities
	double FLVel;
	double FRVel;
	double RLVel;
	double RRVel;

	//Wheel angle differences from robot angle
	double deltaFL;
	double deltaFR;
	double deltaRL;
	double deltaRR;

	double CorrectSteerSetpoint(double setpoint);
	void SetSteerSetpoint(float FLSetPoint, float FRSetPoint, float RLSetPoint, float RRSetPoint);
	void SetDriveSpeed(float FLSpeed, float FRSpeed, float RLSpeed, float RRSpeed);
	void CurrentLimit();

	float FLSOTimer;
	float FRSOTimer;
	float RLSOTimer;
	float RRSOTimer;

	float lastx;
	float lasty;
	float lasttwist;

	bool DriveBackFlag;

public:
	PIDController*     frontLeft;
	SpeedController*   frontLeftDrive;
	AnalogChannelVolt* frontLeftPos;
	SpeedController*   frontLeftSteer;

	PIDController*     frontRight;
	SpeedController*   frontRightDrive;
	AnalogChannelVolt* frontRightPos;
	SpeedController*   frontRightSteer;

	PIDController*     rearLeft;
	SpeedController*   rearLeftDrive;
	AnalogChannelVolt* rearLeftPos;
	SpeedController*   rearLeftSteer;

	PIDController*     rearRight;
	SpeedController*   rearRightDrive;
	AnalogChannelVolt* rearRightPos;
	SpeedController*   rearRightSteer;

	DriveTrain();
	void SetWheelbase(float w, float x, float y);
	void SetMaxSpeed(float MaxSpeed);
	void SetOffsets(double FLOff, double FROff, double RLOff, double RROff);
	void ToggleFrontBack();
	void outputLED();
	void InitDefaultCommand();
	void Steer(float radian, float speed, float a);
	void Crab(float twist, float y, float x, bool operatorControl);
	bool ResetTurns();
	void Lock();
	void SideLock();
	bool GetDriveBackFlag();
	void SetDriveBackFlag(bool flag);
	bool unwind();
	void doneunwind();
	bool unwindwheel(AnalogChannelVolt*, PIDController*);
	void GyroCrab(float desiredangle, float y, float x, bool operatorControl);
	void FieldCentricCrab(float twist, float y, float x, bool operatorControl);
};

#endif

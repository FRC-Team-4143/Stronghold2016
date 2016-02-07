#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

PIDController*     RobotMap::driveTrainFrontLeft = nullptr;
SpeedController*   RobotMap::driveTrainFrontLeftDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainFrontLeftPos = nullptr;
SpeedController*   RobotMap::driveTrainFrontLeftSteer = nullptr;

PIDController*     RobotMap::driveTrainFrontRight = nullptr;
SpeedController*   RobotMap::driveTrainFrontRightDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainFrontRightPos = nullptr;
SpeedController*   RobotMap::driveTrainFrontRightSteer = nullptr;

PIDController*     RobotMap::driveTrainRearLeft = nullptr;
SpeedController*   RobotMap::driveTrainRearLeftDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainRearLeftPos = nullptr;
SpeedController*   RobotMap::driveTrainRearLeftSteer = nullptr;

PIDController*     RobotMap::driveTrainRearRight = nullptr;
SpeedController*   RobotMap::driveTrainRearRightDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainRearRightPos = nullptr;
SpeedController*   RobotMap::driveTrainRearRightSteer = nullptr;

I2C* RobotMap::i2c = nullptr;

SerialPort* RobotMap::serialPort = nullptr;

SpeedController* RobotMap::leftFront;
SpeedController* RobotMap::rightRear;
SpeedController* RobotMap::rightFront;
SpeedController* RobotMap::leftRear;

SpeedController* RobotMap::armMotor;

#ifdef USE_NAVX
KauaiNavX::AHRS* RobotMap::imu = nullptr;
#else
AHRS* RobotMap::imu = nullptr;
#endif

#define CONTINUOUS true
#define P 0.8
#define I 0.0
#define D 0.1
#define F 0.0
#define POTMIN 0.0
#define POTMAX 5.0
#define STEERPOW  1.0
#define TOLERANCE 0.2
#define PERIOD .02
#define RATIO 1

#define FLD 2
#define FLP 2
#define FLS 2

#define FRD 1
#define FRP 1
#define FRS 4

#define RLD 3
#define RLP 3
#define RLS 1

#define RRD 0
#define RRP 0
#define RRS 3

void RobotMap::init() {

    LiveWindow *lw = LiveWindow::GetInstance();

    //serialPort = new SerialPort(57600, SerialPort::kOnboard);
    imu = new AHRS(SerialPort::Port::kUSB);//serialPort, 100);

    driveTrainFrontLeftDrive = new Victor(FLD);
	driveTrainFrontLeftPos   = new AnalogChannelVolt(FLP, true, RATIO);
	driveTrainFrontLeftSteer = new CANTalon(FLS);
	driveTrainFrontLeft      = new PIDController(P, I, D, F, driveTrainFrontLeftPos, driveTrainFrontLeftSteer, PERIOD);
	driveTrainFrontLeft->SetContinuous(CONTINUOUS);
	driveTrainFrontLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontLeft->SetInputRange(POTMIN, POTMAX);
	driveTrainFrontLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainFrontRightDrive = new Victor(FRD);
	driveTrainFrontRightPos   = new AnalogChannelVolt(FRP, true, RATIO);
	driveTrainFrontRightSteer = new CANTalon(FRS);
	driveTrainFrontRight      = new PIDController(P, I, D, F, driveTrainFrontRightPos, driveTrainFrontRightSteer, PERIOD);
	driveTrainFrontRight->SetContinuous(CONTINUOUS);
	driveTrainFrontRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontRight->SetInputRange(POTMIN, POTMAX);
	driveTrainFrontRight->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearLeftDrive = new Victor(RLD);
	driveTrainRearLeftPos   = new AnalogChannelVolt(RLP, true, RATIO);
	driveTrainRearLeftSteer = new CANTalon(RLS);
	driveTrainRearLeft      = new PIDController(P, I, D, F, driveTrainRearLeftPos, driveTrainRearLeftSteer, PERIOD);
	driveTrainRearLeft->SetContinuous(CONTINUOUS);
	driveTrainRearLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearLeft->SetInputRange(POTMIN, POTMAX);
	driveTrainRearLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearRightDrive = new Victor(RRD);
	driveTrainRearRightPos   = new AnalogChannelVolt(RRP, true, RATIO);
	driveTrainRearRightSteer = new CANTalon(RRS);
	driveTrainRearRight      = new PIDController(P, I, D, F, driveTrainRearRightPos, driveTrainRearRightSteer, PERIOD);
	driveTrainRearRight->SetContinuous(CONTINUOUS);
	driveTrainRearRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearRight->SetInputRange(POTMIN, POTMAX);
	driveTrainRearRight->SetOutputRange(-STEERPOW, STEERPOW);

    i2c = new I2C((I2C::Port) 1, 0x04);

    leftFront = new Talon(8);
    rightRear = new Talon(7);
    rightFront = new Talon(5);
    leftRear = new Talon(6);
    
    armMotor = new Talon(0);

}

 #include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

const bool RobotMap::SpeedControl = 1;

PIDController*     RobotMap::driveTrainFrontLeft = nullptr;
CANTalon*   RobotMap::driveTrainFrontLeftDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainFrontLeftPos = nullptr;
CANTalon*   RobotMap::driveTrainFrontLeftSteer = nullptr;

PIDController*     RobotMap::driveTrainFrontRight = nullptr;
CANTalon*   RobotMap::driveTrainFrontRightDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainFrontRightPos = nullptr;
CANTalon*   RobotMap::driveTrainFrontRightSteer = nullptr;

PIDController*     RobotMap::driveTrainRearLeft = nullptr;
CANTalon*   RobotMap::driveTrainRearLeftDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainRearLeftPos = nullptr;
CANTalon*   RobotMap::driveTrainRearLeftSteer = nullptr;

PIDController*     RobotMap::driveTrainRearRight = nullptr;
CANTalon*   RobotMap::driveTrainRearRightDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainRearRightPos = nullptr;
CANTalon*   RobotMap::driveTrainRearRightSteer = nullptr;

I2C* RobotMap::i2c = nullptr;

SerialPort* RobotMap::serialPort = nullptr;

CANTalon* RobotMap::leftFront;
CANTalon* RobotMap::rightRear;
CANTalon* RobotMap::rightFront;
CANTalon* RobotMap::leftRear;
SpeedController* RobotMap::feeder;

CANTalon* RobotMap::armMotor;

CANTalon* RobotMap::winchMotor;
AnalogInput* RobotMap::winchPot;
PIDController* RobotMap::shooterWinch;

DigitalInput* RobotMap::testDigital;
AnalogInput* RobotMap::feederSensor;

#ifdef USE_NAVX
KauaiNavX::AHRS* RobotMap::imu = nullptr;
#else
AHRS* RobotMap::imu = nullptr;
#endif

#define CONTINUOUS true
#define P 0.7
#define I 0.0
#define D 0.0
#define F 0.0
#define driveP 0.3
#define driveI 0.0
#define driveD 0.0
#define driveF 0.1
#define POTMIN 0.0
#define POTMAX 5.0
#define STEERPOW  0.6
#define TOLERANCE 0.2
#define PERIOD .02
#define RATIO 1

#define FLD 12
#define FLP 2
#define FLS 2

#define FRD 11
#define FRP 5
#define FRS 1

#define RLD 14
#define RLP 3
#define RLS 4

#define RRD 13
#define RRP 4
#define RRS 3

void RobotMap::init() {
    //LiveWindow *lw = LiveWindow::GetInstance();

    //serialPort = new SerialPort(57600, SerialPort::kOnboard);
    imu = new AHRS(SPI::kOnboardCS0);//serialPort, 100);

////////////////////////////////////
////Front Left Wheel////////////////
////////////////////////////////////
    driveTrainFrontLeftDrive = new CANTalon(FLD);
	driveTrainFrontLeftDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainFrontLeftDrive->ConfigPeakOutputVoltage(12.0, -12.0);
	if (SpeedControl){
		driveTrainFrontLeftDrive->SetControlMode(CANSpeedController::kSpeed);
		driveTrainFrontLeftDrive->SetP(driveP);
		driveTrainFrontLeftDrive->SetI(driveI);
		driveTrainFrontLeftDrive->SetD(driveD);
		driveTrainFrontLeftDrive->SetF(driveF);
		driveTrainFrontLeftDrive->SetSensorDirection(true);
	}
	driveTrainFrontLeftSteer = new CANTalon(FLS);
	driveTrainFrontLeftSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainFrontLeftPos   = new AnalogChannelVolt(FLP, true, RATIO, driveTrainFrontLeftSteer);
	driveTrainFrontLeft      = new PIDController(P, I, D, F, driveTrainFrontLeftPos, driveTrainFrontLeftSteer, PERIOD);
	driveTrainFrontLeft->SetContinuous(CONTINUOUS);
	driveTrainFrontLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontLeft->SetOutputRange(-STEERPOW, STEERPOW);

////////////////////////////////////
////Front Right Wheel///////////////
////////////////////////////////////
	driveTrainFrontRightDrive = new CANTalon(FRD);
	driveTrainFrontRightDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainFrontRightDrive->ConfigPeakOutputVoltage(12.0, -12.0);
	if (SpeedControl){
		driveTrainFrontRightDrive->SetControlMode(CANSpeedController::kSpeed);
		driveTrainFrontRightDrive->SetP(driveP);
		driveTrainFrontRightDrive->SetI(driveI);
		driveTrainFrontRightDrive->SetD(driveD);
		driveTrainFrontRightDrive->SetF(driveF);
		driveTrainFrontRightDrive->SetSensorDirection(true);
	}
	driveTrainFrontRightSteer = new CANTalon(FRS);
	driveTrainFrontRightSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainFrontRightPos   = new AnalogChannelVolt(FRP, true, RATIO, driveTrainFrontRightSteer);
	driveTrainFrontRight      = new PIDController(P, I, D, F, driveTrainFrontRightPos, driveTrainFrontRightSteer, PERIOD);
	driveTrainFrontRight->SetContinuous(CONTINUOUS);
	driveTrainFrontRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontRight->SetOutputRange(-STEERPOW, STEERPOW);

////////////////////////////////////
////Rear Left Wheel/////////////////
////////////////////////////////////
	driveTrainRearLeftDrive = new CANTalon(RLD);
	driveTrainRearLeftDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainRearLeftDrive->ConfigPeakOutputVoltage(12.0, -12.0);
	if (SpeedControl){
		driveTrainRearLeftDrive->SetControlMode(CANSpeedController::kSpeed);
		driveTrainRearLeftDrive->SetP(driveP);
		driveTrainRearLeftDrive->SetI(driveI);
		driveTrainRearLeftDrive->SetD(driveD);
		driveTrainRearLeftDrive->SetF(driveF);
		driveTrainRearLeftDrive->SetSensorDirection(true);
	}
	driveTrainRearLeftSteer = new CANTalon(RLS);
	driveTrainRearLeftSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainRearLeftPos   = new AnalogChannelVolt(RLP, true, RATIO, driveTrainRearLeftSteer);
	driveTrainRearLeft      = new PIDController(P, I, D, F, driveTrainRearLeftPos, driveTrainRearLeftSteer, PERIOD);
	driveTrainRearLeft->SetContinuous(CONTINUOUS);
	driveTrainRearLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearLeft->SetOutputRange(-STEERPOW, STEERPOW);

////////////////////////////////////
////Rear Right Wheel////////////////
////////////////////////////////////
	driveTrainRearRightDrive = new CANTalon(RRD);
	driveTrainRearRightDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainRearRightDrive->ConfigPeakOutputVoltage(12.0, -12.0);
	if (SpeedControl){
		driveTrainRearRightDrive->SetControlMode(CANSpeedController::kSpeed);
		driveTrainRearRightDrive->SetP(driveP);
		driveTrainRearRightDrive->SetI(driveI);
		driveTrainRearRightDrive->SetD(driveD);
		driveTrainRearRightDrive->SetF(driveF);
		driveTrainRearRightDrive->SetSensorDirection(true);
	}
	driveTrainRearRightSteer = new CANTalon(RRS);
	driveTrainRearRightSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainRearRightPos   = new AnalogChannelVolt(RRP, true, RATIO, driveTrainRearRightSteer);
	driveTrainRearRight = new PIDController(P, I, D, F, driveTrainRearRightPos, driveTrainRearRightSteer, PERIOD);
	driveTrainRearRight->SetContinuous(CONTINUOUS);
	driveTrainRearRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearRight->SetInputRange(POTMIN, POTMAX);
	driveTrainRearRight->SetOutputRange(-STEERPOW, STEERPOW);

    i2c = new I2C((I2C::Port) 1, 0x04);

    rightRear = new CANTalon(9);
    leftFront = new CANTalon(7);
    rightFront = new CANTalon(8);
    leftRear = new CANTalon(10);
    feeder = new Talon(0);
    
    armMotor = new CANTalon(6);

    winchMotor = new CANTalon(5);
    winchPot = new AnalogInput(1);
    shooterWinch = new PIDController(0.8, 0.0, 0.05, 0.0, winchPot, winchMotor);

    testDigital = new DigitalInput(0);
    feederSensor = new AnalogInput(0);
    feederSensor->SetAverageBits(2);
    feederSensor->SetOversampleBits(4);
    feederSensor->SetSampleRate(1000);
}

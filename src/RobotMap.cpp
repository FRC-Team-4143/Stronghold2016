#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

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

SpeedController* RobotMap::leftFront;
SpeedController* RobotMap::rightRear;
SpeedController* RobotMap::rightFront;
SpeedController* RobotMap::leftRear;
SpeedController* RobotMap::feeder;

SpeedController* RobotMap::armMotor;

DoubleSolenoid* RobotMap::pickupSolenoid;
Compressor* RobotMap::compressor;

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

#define FLD 12
#define FLP 2
#define FLS 2

#define FRD 11
#define FRP 1
#define FRS 1

#define RLD 14
#define RLP 3
#define RLS 4

#define RRD 13
#define RRP 0
#define RRS 3

void RobotMap::init() {
    //serialPort = new SerialPort(57600, SerialPort::kOnboard);
    imu = new AHRS(SPI::kOnboardCS0);//serialPort, 100);

    driveTrainFrontLeftDrive = new CANTalon(FLD);
	driveTrainFrontLeftDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainFrontLeftDrive->ConfigEncoderCodesPerRev(1024);
	driveTrainFrontLeftSteer = new CANTalon(FLS);
	driveTrainFrontLeftSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainFrontLeftSteer->ConfigEncoderCodesPerRev(360);
	driveTrainFrontLeftPos   = new AnalogChannelVolt(FLP, true, RATIO, driveTrainFrontLeftSteer);
	driveTrainFrontLeft      = new PIDController(P, I, D, F, driveTrainFrontLeftPos, driveTrainFrontLeftSteer, PERIOD);
	driveTrainFrontLeft->SetContinuous(CONTINUOUS);
	driveTrainFrontLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainFrontRightDrive = new CANTalon(FRD);
	driveTrainFrontRightDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainFrontRightDrive->ConfigEncoderCodesPerRev(1024);
	driveTrainFrontRightSteer = new CANTalon(FRS);
	driveTrainFrontRightSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainFrontRightSteer->ConfigEncoderCodesPerRev(360);
	driveTrainFrontRightPos   = new AnalogChannelVolt(FRP, true, RATIO, driveTrainFrontRightSteer);
	driveTrainFrontRight      = new PIDController(P, I, D, F, driveTrainFrontRightPos, driveTrainFrontRightSteer, PERIOD);
	driveTrainFrontRight->SetContinuous(CONTINUOUS);
	driveTrainFrontRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontRight->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearLeftDrive = new CANTalon(RLD);
	driveTrainRearLeftDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainRearLeftDrive->ConfigEncoderCodesPerRev(1024);
	driveTrainRearLeftSteer = new CANTalon(RLS);
	driveTrainRearLeftSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainRearLeftSteer->ConfigEncoderCodesPerRev(360);
	driveTrainRearLeftPos   = new AnalogChannelVolt(RLP, true, RATIO, driveTrainRearLeftSteer);
	driveTrainRearLeft      = new PIDController(P, I, D, F, driveTrainRearLeftPos, driveTrainRearLeftSteer, PERIOD);
	driveTrainRearLeft->SetContinuous(CONTINUOUS);
	driveTrainRearLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearRightDrive = new CANTalon(RRD);
	driveTrainRearRightDrive->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	driveTrainRearRightDrive->ConfigEncoderCodesPerRev(1024);
	driveTrainRearRightSteer = new CANTalon(RRS);
	driveTrainRearRightSteer->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	driveTrainRearRightSteer->ConfigEncoderCodesPerRev(360);
	driveTrainRearRightPos   = new AnalogChannelVolt(RRP, true, RATIO, driveTrainRearRightSteer);
	driveTrainRearRight = new PIDController(P, I, D, F, driveTrainRearRightPos, driveTrainRearRightSteer, PERIOD);
	driveTrainRearRight->SetContinuous(CONTINUOUS);
	driveTrainRearRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearRight->SetInputRange(POTMIN, POTMAX);
	driveTrainRearRight->SetOutputRange(-STEERPOW, STEERPOW);

    i2c = new I2C((I2C::Port) 1, 0x04);

    rightRear = new Talon(3);
    leftFront = new Talon(4);
    rightFront = new Talon(5);
    leftRear = new Talon(6);
    feeder = new Talon(2);
    
    armMotor = new Talon(0);

    compressor = new Compressor(0);
    pickupSolenoid = new DoubleSolenoid(5, 0, 1);

}

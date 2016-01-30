// ==========================================================================
// Logger class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#include "Logger.h"
#include <WPILib.h>

Logger::Logger() {
}

void Logger::Log(std::string msg) {
	//DriverStation::ReportError(msg.append("\r\n"));
	std::cout << msg << std::endl;
}

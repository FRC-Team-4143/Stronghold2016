// ==========================================================================
// Logger class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
	Logger();

	static void Log(std::string msg);
};

#define LOG(msg) Logger::Log(msg);

#endif

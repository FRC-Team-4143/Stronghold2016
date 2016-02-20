#include "VisionBridgeSub.h"
#include "../RobotMap.h"
#include "../Modules/CastUtil.h"

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <condition_variable>
#include <iostream>

const uint16_t DEFAULT_LISTENING_PORT = 4143;

#define MAX_PACKET_SIZE 2048

VisionBridgeSub::VisionBridgeSub()
:	VisionBridgeSub(DEFAULT_LISTENING_PORT)
{
}

VisionBridgeSub::VisionBridgeSub(uint16_t listeningPort)
:	Subsystem("VisionBridgeSub"),
	_mutex(),
	_listeningPort(listeningPort),
	_position(0),
	_debug(false),
	_listeningThread(&VisionBridgeSub::Listen, this)
{
}

void VisionBridgeSub::InitDefaultCommand() {
	//SetDefaultCommand(new MySpecialCommand());
}

void VisionBridgeSub::EnableDebug(bool debug) {
	_debug = debug;
}

double VisionBridgeSub::GetPosition() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	return _position;
}

void VisionBridgeSub::DebugOutput(std::string packet) {
	std::cout << "[DEBUG] visionPacket=" << packet << std::endl;
}

void VisionBridgeSub::Listen() {
	sockaddr_in  serverAddr;   // server's socket address
	sockaddr_in  clientAddr;   // client's socket address
	socklen_t    sockAddrSize; // size of socket address structure
	int          sockListener; // socket file descriptor
	char buf[MAX_PACKET_SIZE + 1];

	// Set up the local address.
	sockAddrSize = sizeof(sockaddr_in);
	bzero(&serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(_listeningPort);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	std::cout << GetName() << " Starting UDP listener on port " << _listeningPort << std::endl;

	// Create a UDP socket.
	if ((sockListener = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR) {
		perror("socket");
		return;
	}
    std::cout << GetName() << " Created socket" << std::endl;

    // Bind socket to local address.
	if (bind(sockListener, S_CAST(sockaddr*, S_CAST(void*, &serverAddr)), sockAddrSize) == ERROR) {
		perror("bind");
		close(sockListener);
		return;
	}
	std::cout << GetName() << " Bound socket" << std::endl;

	for (;;) {
		//if (_debug) std::cout << "[DEBUG] " << GetName() << " Waiting on port" << std::endl;
		int recvlen = recvfrom(sockListener, buf, sizeof(buf) - 1, 0, S_CAST(sockaddr*, S_CAST(void*, &clientAddr)), &sockAddrSize);
		//if (_debug) std::cout << "[DEBUG] " << GetName() << " Received " << recvlen << " bytes" << std::endl;
		if (recvlen > 0) {
			buf[recvlen] = 0;
			ParsePacket(buf);
		}
	}

	close(sockListener);
}

void VisionBridgeSub::ParsePacket(std::string packet) {
	if (_debug) DebugOutput(packet);
	try {
		auto position = std::stof(packet);
		SetPosition(position);
	}
	catch (...) {
	}
}

void VisionBridgeSub::SetPosition(double position) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	_position = position;
}

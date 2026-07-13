#include "Host.hpp"

// TODO: REFACTOR THIS SHIT
// 		 create a struct called HostInfo in a seprate file.
// 		 will contain _name, _IPv4Addr, _MacAddr and _status,
// 		 this will help provide an interface (the host class) for
// 		 working with hosts and Json in a non-circular dependent way.

Host::Host(const std::string& name, const std::string& IPv4Addr, const std::string& MACAddr, const bool status){
    _name = name;
    _IPv4Addr = IPv4Addr;
    _MACAddr = MACAddr;
    _status = status;
}

// getters
std::string Host::getName() const {
    return _name;
}
std::string Host::getIPv4() const {
    return _IPv4Addr;
}
std::string Host::getMAC() const {
    return _MACAddr;
}
bool Host::getStatus() const {
    return _status;
}

// setters
void Host::setName(const std::string& name) {
    _name = name;
}
void Host::setIPv4Address(const std::string& IPv4Addr) {
    _IPv4Addr = IPv4Addr;
}
void Host::setMACAddress(const std::string& MACAddr) {
    _MACAddr = MACAddr;
}
void Host::setStatus(const bool status) {
    _status = status;
}

std::ostream& operator<<(std::ostream& os, const Host& host) {
	// TODO: change these to a struct called TableContext? could
	// 		 be useful...
	int nameColumnMargin = 20;
	int IPv4ColumnMargin = 15;
	int MACColumnMargin = 20;
	int statusColumnMargin = 15;

	std::string hostName = host.getName();
	std::string hostIPv4 = host.getIPv4();
	std::string hostMAC = host.getMAC();
	bool hostStatus = host.getStatus();

	os << std::left;

	os << std::setw(nameColumnMargin) << hostName << RESET;
	os << std::setw(IPv4ColumnMargin) << hostIPv4 << RESET;
	os << std::setw(MACColumnMargin) << hostMAC << RESET;
	os << std::setw(statusColumnMargin) << (hostStatus ? "online" : "offline") << RESET;

	return os;
}

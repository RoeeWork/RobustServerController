#include "Host.hpp"

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
std::string Host::getIPv4Address() const {
    return _IPv4Addr;
}
std::string Host::getMACAddress() const {
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
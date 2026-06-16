#pragma once
#include "../utils.h"
class Host
{
public:
    Host(const std::string& name,const std::string& IPv4,const std::string& MAC, const bool status);
    // getters
    std::string getName() const;
    std::string getIPv4() const;
    std::string getMAC() const;
    bool getStatus() const;

    // setters
    void setName(const std::string& name);
    void setIPv4Address(const std::string& IPv4Addr);
    void setMACAddress(const std::string& MACAddr);
    void setStatus(const bool status);
private:
   	std::string _name; // the host given name
	std::string _IPv4Addr;
	std::string _MACAddr;
	bool _status; // offline-online
};
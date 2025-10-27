/* utils.h */

#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <array>


struct host_info {
	std::string name;
	std::string IPv4;
	std::string MAC;
};


// uses arpScanOutput(), parses the ip and MAC address , returns them in a map<mac, ip>.
std::map<std::string, std::string> parsedArpOutput();

// uses popen() to get arp-scan output, and saves each 
// line to a vector EXCEPT for the first two lines (the header) 
// and last three lines (the trailer).
std::vector<std::string> arpScanOutput();
void PrintOut(std::map<std::string, std::string> parsedout);

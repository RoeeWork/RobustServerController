/* AddServers.cpp */

#include "Commands.h"

std::vector<host_info> AddServers::Start() {

	std::vector<host_info> scannedAddrs;
	std::vector<host_info> scannedAddrsTemp;

	std::cout << "[AddServers::Start()] scanning hosts on LAN...";
	std::map<std::string, std::string> hostsStrings = parsedArpOutput();
	std::cout << "[AddServers::Start()] Done!";
	for (const auto &p : hostsStrings) {
		std::string mac_addr = p.first;
		std::string ipv4 = p.second;
		host_info currhost;
		currhost.IPv4 = ipv4;
		currhost.MAC = mac_addr;
		scannedAddrsTemp.push_back(currhost);
	}
	PrintOut(hostsStrings);
}


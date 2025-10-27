/* AddServers.cpp */

#include "Commands.h"

AddServers::AddServers() {}

std::vector<host_info> AddServers::Start() {

	std::vector<host_info> chosenAddrs;
	std::vector<host_info> chosenAddrsTemp;

	std::cout << "[AddServers::Start()] scanning hosts on LAN..." << std::endl;
	std::vector<std::pair<std::string, std::string>> hostsStrings = parsedArpOutput();
	std::cout << "[AddServers::Start()] Done!\n";
	for (const auto &p : hostsStrings) {
		std::string mac_addr = p.first;
		std::string ipv4 = p.second;
		host_info currhost;
		currhost.IPv4 = ipv4;
		currhost.MAC = mac_addr;
		chosenAddrsTemp.push_back(currhost);
	}

	while (true) {
		PrintOut(hostsStrings);

		int hostNum;

		std::cout << "[AddServers::Start()] choose host number (-1 if done): ";
		std::cin >> hostNum;

		if (!std::cin) {
			std::cout << "[AddServers::Start()] please input a valid number.\n" << std::endl;
			continue;
		}
		if (hostNum == -1) {
			if (chosenAddrs.size() == 0) {
				std::cout << "[AddServers::Start()] didnt choose any hosts, stopping...\n" << std::endl;

				return chosenAddrs;
			}
			else {
				std::cout << "[AddServers::Start()] stopping...\n" << std::endl;

				break;
			}
		}
		if (hostNum > hostsStrings.size()) {
			std::cout << "[AddServers::Start()] please input a number that is in range.\n" << std::endl;

			continue;
		}
		
		host_info currhost = chosenAddrsTemp[hostNum - 1];
		std::string hostName;
		std::cout << "[AddServers::Start()] Name your server: ";

		std::cin >> hostName;
		currhost.name = hostName;
		chosenAddrs.push_back(currhost);
		std::cout << "[AddServers::Start()] done! \n " << std::endl;
	}
	
	for (auto &i: chosenAddrs) { this->chosenHosts.push_back(i); }
	return chosenAddrs;
}


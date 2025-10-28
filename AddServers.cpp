/* AddServers.cpp */

#include "Commands.h"
#include "json_utils.h"

AddServers::AddServers() {}

std::vector<host_info> AddServers::Start() {
	verbose_print("[AddServers::Start()] starting Addserver::Start().\n", verbose);
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

	int hostNum;
	while (true) {
		PrintOut(hostsStrings);

		std::cout << "[AddServers::Start()] choose host number (-1 if done): ";
		std::string num;
		std::getline(std::cin, num);
		try {
			hostNum = stoi(num);
		}
		catch (std::invalid_argument) {
			std::cout << "[AddServers::Start()] please input a valid number.\n" << std::endl;
			continue;
		}
		if (!std::cin) {
			std::cout << "[AddServers::Start()] please input a valid number.\n" << std::endl;
			hostNum = 0;
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
		if (hostNum > hostsStrings.size() || (hostNum <= 0 && hostNum != -1)) {
			std::cout << "[AddServers::Start()] please input a number that is in range.\n" << std::endl;

			continue;
		}
		
		host_info currhost = chosenAddrsTemp[hostNum - 1];
		std::string hostName;

		std::cout << "[AddServers::Start()] Name your server: ";
		std::getline(std::cin, hostName);

		currhost.name = hostName;
		chosenAddrs.push_back(currhost);
	}
	
	verbose_print("[AddServers::Start()] done... starting save\n ", verbose);
	SaveAddrs(chosenAddrs);
	UpdateHosts();
 
	std::cout << "[AddServers::Start()] done!\n";
	return chosenAddrs;
}

void AddServers::SaveAddrs(std::vector<host_info> addedHosts) {
	verbose_print("[AddServers::SaveAddrs()] saving selected hosts.\n", verbose);
	if (addedHosts.size() != 0) {
		if (!std::filesystem::exists(root / "serverinfo.json")) {
			std::ofstream file("root / serverinfo.json");
			file << "[]";
			file.close();
		}

		json j_hosts_data = json::array();

		std::ifstream infile("root / serverinfo.json");
		if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
			try {
				infile >> j_hosts_data;
				if ( !j_hosts_data.is_array()) {
	                std::cerr << "[AddServers::SaveAddrs()] Warning: JSON is not an array. Resetting.\n";
					j_hosts_data = json::array();
				}
			}
			catch (json::parse_error &e) {
	                std::cerr << "[AddServers::SaveAddrs()] ERROR: parse error. Resetting.\n";
					j_hosts_data = json::array();
			}
		}
		infile.close();

		json j_hosts = addedHosts;
		for (auto &h : j_hosts) {
			j_hosts_data.push_back(h);
		}
		std::ofstream outfile(root / "serverinfo.json");
		outfile << j_hosts_data.dump(4);
		outfile.close();
	}
	this->isFirstRun = false;
	verbose_print("[AddServers::SaveAddrs()] done!\n", verbose);
}



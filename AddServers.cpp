/* AddServers.cpp */

#include "Commands.h"
#include "json_utils.h"

AddServers::AddServers() {}

std::vector<host_info> AddServers::Start() {
	verbose_print("[AddServers::Start()] starting Addserver::Start().", verbose);
	std::vector<host_info> chosenAddrs;
	std::vector<host_info> chosenAddrsTemp;

	std::cout << "[AddServers::Start()] scanning hosts on LAN..." << std::endl;
	std::vector<std::pair<std::string, std::string>> hostsStrings = parsedArpOutput();
	

	for (const auto &p : hostsStrings) {
		std::string mac_addr = p.first;
		std::string ipv4 = p.second;
		host_info currhost;
		currhost.IPv4 = ipv4;
		currhost.MAC = mac_addr;
		chosenAddrsTemp.push_back(currhost);
	}

	std::cout << "[AddServers::Start()] Done!\n";
	int hostNum;

	verbose_print("[AddServers::Start()] starting host select loop...", verbose);
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
		catch (std::out_of_range) {
			std::cout << "[AddServers::Start()] number out of range.\n" << std::endl;
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
	
	verbose_print("[AddServers::Start()] done... starting save ", verbose);
	SaveAddrs(chosenAddrs);
	UpdateHosts();
 
	std::cout << "[AddServers::Start()] done!\n";
	return chosenAddrs;
}

void AddServers::SaveAddrs(std::vector<host_info> addedHosts) {
	verbose_print("[AddServers::SaveAddrs()] starting AddServers::SaveAddrs().", verbose);
	verbose_print("[AddServers::SaveAddrs()] saving selected hosts.", verbose);
	if (addedHosts.size() != 0) {
		try {
			verbose_print("[AddServers::SaveAddrs()] checking if serverinfo.json exists...", verbose);
			if (!std::filesystem::exists(root / "serverinfo.json")) {
				verbose_print("[AddServers::SaveAddrs()] attempting to create serverinfo.json...", verbose);
				std::ofstream file(root / "serverinfo.json");
				file << "[]";
				file.close();
			}
		}
		catch (std::exception &e) {
			throw std::runtime_error(RED + std::string("[AddServers::SaveAddrs()] FILE ERROR: cant create serverinfo.json: ") + e.what());
		}
		json j_hosts_data = json::array();

		verbose_print("[AddServers::SaveAddrs()] attempting to read serverinfo.json...", verbose);
		std::ifstream infile(root / "serverinfo.json");
		if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
			try {
				verbose_print("[AddServers::SaveAddrs()] attempting to parse serverinfo.json...", verbose);
				infile >> j_hosts_data;
				if ( !j_hosts_data.is_array()) {
	                std::cerr << "[AddServers::SaveAddrs()] Warning: JSON is not an array. Resetting.";
					j_hosts_data = json::array();
				}
			}
			catch (json::parse_error &e) {
	                std::cerr << "[AddServers::SaveAddrs()] ERROR: parse error. Resetting.";
					j_hosts_data = json::array();
			}
		}
		infile.close();

		json j_hosts = addedHosts;
		for (auto &h : j_hosts) {
			j_hosts_data.push_back(h);
		}
		try {
			verbose_print("[AddServers::SaveAddrs()] attempting to write to serverinfo.json...", verbose);
			std::ofstream outfile(root / "serverinfo.json");
			outfile << j_hosts_data.dump(4);
			outfile.close();
		}
		catch (std::exception &e) {
		    throw std::runtime_error(std::string("[AddServers::SaveAddrs()] FILE WRITE ERROR: ") + e.what());
		}
	}
	this->isFirstRun = false;
	verbose_print("[AddServers::SaveAddrs()] done!", verbose);
}



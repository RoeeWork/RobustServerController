/* Commands.cpp */

#include "Commands.h"
#include "json_utils.h"

Commands::Commands() {
	UpdateHosts();
	bool isFirstRun;

	if (!std::filesystem::exists(root / "firstrun.json")) {
		std::ofstream file(root / "firstrun.json");
		file << "{}";
		file.close();
	}

	json j_isFirstRun; 

	std::ifstream infile(root / "firstrun.json");
	if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
		try {
			infile >> j_isFirstRun;
		}
		catch (json::parse_error &e) {
			std::cerr << "[Commands::Commands()] ERROR: parse error. Resetting.\n";
		}
	}

	infile.close();
	
	if (j_isFirstRun.contains("isFirstRun") && j_isFirstRun["isFirstRun"].is_boolean()) {
		bool isFirstRun = j_isFirstRun["isFirstRun"].get<bool>();
	}

	else {
		std::ofstream outfile(root / "firstrun.json");
		j_isFirstRun["isFirstRun"] = true;
		isFirstRun = true;
		outfile << j_isFirstRun;
		outfile.close();
	}

	if(isFirstRun) {
		AddServers add;
		add.Start();
		std::ofstream outfile(root / "firstrun.json");
		j_isFirstRun["isFirstRun"] = false;
		isFirstRun = false;
		outfile << j_isFirstRun;
		outfile.close();
	}
	this->isFirstRun = isFirstRun;
	UpdateHosts();
}

void Commands::UpdateHosts() {
	json j_hosts_data;

	if (!std::filesystem::exists(root / "serverinfo.json")) {
		std::ofstream file(root / "serverinfo.json");
		file << "[]";
		file.close();
	}

	j_hosts_data = json::array();

	std::ifstream infile(root / "serverinfo.json");
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

	std::vector<host_info> hosts = j_hosts_data.get<std::vector<host_info>>();
	this->chosenHosts.clear();
		for (auto &host : hosts) {
		this->chosenHosts.push_back(host);
	}
}

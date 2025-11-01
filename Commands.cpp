/* Commands.cpp */

#include "Commands.h"
#include "json_utils.h"

Commands::Commands() {
	verbose_print("[Commands::Commands()] starting Commands::Commands()", verbose);
	UpdateHosts();
	bool isFirstRun;
	try {
		verbose_print("[Commands::Commands()] attempting to find firstrun.json...", verbose);
		if (!std::filesystem::exists(root / "firstrun.json")) {
			verbose_print("[Commands::Commands()] attempting to create firstrun.json...", verbose);
			std::ofstream file(root / "firstrun.json");
			file << "{}";
			file.close();
		}
	}
	catch (std::exception &e) {
		throw std::runtime_error(RED + std::string("[AddServers::SaveAddrs()] FILE ERROR: cant create serverinfo.json: ") + e.what());
	}
	
	json j_isFirstRun; 

	verbose_print("[Commands::Commands()] attempting to read firstrun.json...", verbose);
	std::ifstream infile(root / "firstrun.json");
	if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
		try {
			infile >> j_isFirstRun;
		}
		catch (json::parse_error &e) {
			throw std::runtime_error(RED + std::string("[Commands::Commands()] JSON ERROR: Failed to parse firstrun.json:") + e.what());
		}
	}

	verbose_print("[Commands::Commands()] attempting to close firstrun.json...", verbose);
	infile.close();
	
	verbose_print("[Commands::Commands()] attempting to check firstrun value...", verbose);
	if (j_isFirstRun.contains("isFirstRun") && j_isFirstRun["isFirstRun"].is_boolean()) {
		isFirstRun = j_isFirstRun["isFirstRun"].get<bool>();
	}

	else {
		try {
			verbose_print("[Commands::Commands()] attempting to write to firstrun.json...", verbose);
			std::ofstream outfile(root / "firstrun.json");
			j_isFirstRun["isFirstRun"] = true;
			isFirstRun = true;
			outfile << j_isFirstRun;
			outfile.close();
		}
		catch (const std::exception &e) {
			throw std::runtime_error(std::string("[Commands::Commands()] FILE WRITE ERROR: ") + e.what());
		}
	}

	if(isFirstRun) {
		try {
			std::ofstream outfile(root / "firstrun.json");
			j_isFirstRun["isFirstRun"] = false;
			isFirstRun = false;
			outfile << j_isFirstRun;
			outfile.close();
			AddServers add;
			add.Start();
		}
		catch (const std::exception &e) {
			throw std::runtime_error(std::string("[Commands::Commands()] FILE WRITE ERROR: ") + e.what());
		}
	}
	this->isFirstRun = isFirstRun;
	UpdateHosts();
}

void Commands::RemoveHost(std::string hostName) {
	verbose_print("[Commands::RemoveHost()] starting Commands::RemoveHost().", verbose);
	json j_hosts_data;
	try {
		verbose_print("[Commands::RemoveHost()] attempting to read serverinfo.json.", verbose);
		if (!std::filesystem::exists(root / "serverinfo.json")) {
			verbose_print("[Commands::RemoveHost()] no serverinfo.json.", verbose);
    		throw std::runtime_error(std::string("[Commands::RemoveHost()] no serverinfo.json - add servers before trying to remove one..."));
		}
	}
	catch (const std::exception &e) {
		verbose_print("[Commands::RemoveHost()] found exception", verbose);
    	throw std::runtime_error(std::string("[Commands::RemoveHost()] FILE ERROR: ") + e.what());
	}
	j_hosts_data = json::array();

	verbose_print("[Commands::RemoveHosts()] attempting to read serverinfo.json.", verbose);
	std::ifstream infile(root / "serverinfo.json");
	if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
		try {
			infile >> j_hosts_data;
			if ( !j_hosts_data.is_array()) {
				verbose_print("[Commands::RemoveHosts()] Warning: JSON is not an array. Resetting.", verbose);
				j_hosts_data = json::array();
			}
		}
		catch (json::parse_error &e) {
				verbose_print("[Commands::RemoveHosts()] found exception", verbose);
				throw std::runtime_error(RED + std::string("[Commands::RemoveHosts()] JSON ERROR: Failed to parse serverinfo.json:") + e.what());
		}
	}
	infile.close();

	for (auto it = j_hosts_data.begin(); it != j_hosts_data.end(); ++it) {
		if (it->contains("Name") && (*it)["Name"] == hostName) {
			verbose_print("[Commands::RemoveHosts()] found host, removing from serverinfo.json...", verbose);
			j_hosts_data.erase(it);
			break;
		}
		else {
			it++;
		}
    }

	try {
		verbose_print("[AddServers::RemoveHosts()] attempting to write to serverinfo.json...", verbose);
		std::ofstream(root / "serverinfo.json", std::ios::trunc) << j_hosts_data.dump(4);
	}
	catch (std::exception &e) {
		throw std::runtime_error(std::string("[AddServers::RemoveHosts()] FILE WRITE ERROR: ") + e.what());
	}
	
	UpdateHosts();
}

void Commands::UpdateHosts() {
	verbose_print("[Commands::UpdateHosts()] starting Commands::UpdateHosts().", verbose);
	json j_hosts_data;
	try {
		verbose_print("[Commands::UpdateHosts()] attempting to read serverinfo.json.", verbose);
		if (!std::filesystem::exists(root / "serverinfo.json")) {
			verbose_print("[Commands::UpdateHosts()] attempting to create serverinfo.json.", verbose);
			std::ofstream file(root / "serverinfo.json");
			file << "[]";
			file.close();
		}
	}
	catch (const std::exception &e) {
		verbose_print("[Commands::UpdateHosts()] found exception", verbose);
    	throw std::runtime_error(std::string("[Commands::UpdateHosts()] FILE ERROR: ") + e.what());
	}
	j_hosts_data = json::array();

	verbose_print("[Commands::UpdateHosts()] attempting to read serverinfo.json.", verbose);
	std::ifstream infile(root / "serverinfo.json");
	if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
		try {
			infile >> j_hosts_data;
			if ( !j_hosts_data.is_array()) {
				verbose_print("[Commands::UpdateHosts()] Warning: JSON is not an array. Resetting.", verbose);
				j_hosts_data = json::array();
			}
		}
		catch (json::parse_error &e) {
				verbose_print("[Commands::UpdateHosts()] found exception", verbose);
				throw std::runtime_error(RED + std::string("[Commands::UpdateHosts()] JSON ERROR: Failed to parse serverinfo.json:") + e.what());
		}
	}
	infile.close();

	std::vector<host_info> hosts = j_hosts_data.get<std::vector<host_info>>();
	this->chosenHosts.clear();
		for (auto &host : hosts) {
		this->chosenHosts.push_back(host);
	}
}

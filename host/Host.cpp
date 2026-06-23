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

// methods
void Host::changeHostName(std::string currName, std::string newName) {
    //verbose_print("[Host::changeHostName()] starting Host.changeHostName()", verbose);
    //code rev -> try and catch need to be one
	json j_hosts_data;
	try {
        validateJsonFileExistence();
	}
	catch (const std::exception &e) {
		verbose_print("[Commands::changeHostName()] found exception", verbose);
    	throw std::runtime_error(std::string("[Commands::RemoveHost()] FILE ERROR: ") + e.what());
	}
	j_hosts_data = json::array();

	verbose_print("[Commands::changeHostName()] attempting to read serverinfo.json.", verbose);
	std::ifstream infile(root / "serverinfo.json");
	if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
		try {
			infile >> j_hosts_data;
			if ( !j_hosts_data.is_array()) {
				verbose_print("[Commands::changeHostName()] Warning: JSON is not an array. Resetting.", verbose);
				j_hosts_data = json::array();
			}
		}
		catch (json::parse_error &e) {
				verbose_print("[Commands::changeHostName()] found exception", verbose);
				throw std::runtime_error(RED + std::string("[Commands::RemoveHosts()] JSON ERROR: Failed to parse serverinfo.json:") + e.what());
		}
	}
	infile.close();

	for (auto it = j_hosts_data.begin(); it != j_hosts_data.end(); ++it) {
		if (it->contains("Name") && (*it)["Name"] == currName) {
			verbose_print("[Commands::changeHostName()] found host, changing name and adding to serverinfo.json...", verbose);
			(*it)["Name"] = newName;
			break;
		}
    }

	try {
		verbose_print("[Commands::changeHostName()] attempting to write to serverinfo.json...", verbose);
		std::ofstream(root / "serverinfo.json", std::ios::trunc) << j_hosts_data.dump(4);
	}

	catch (std::exception &e) {
		throw std::runtime_error(std::string("[Commands::changeHostName()] FILE WRITE ERROR: ") + e.what());
	}
}

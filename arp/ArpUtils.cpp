#include "./ArpUtils.hpp"

// scans LAN for connected hosts, returns a vector of type Host which represents all known hosts in LAN.
std::vector<Host> ArpUtils::scanHosts() {
	std::vector<Host> hosts;
	std::vector<std::pair<std::string, std::string>> hostsStrings = parsedArpOutput();
	

	// convert hosts to host_info
	for (const auto &p : hostsStrings) {
		std::string mac_addr = p.first;
		std::string ipv4 = p.second;
		Host currhost = Host();
		currhost.setIPv4Address(ipv4);
		currhost.setMACAddress(mac_addr);
		hosts.push_back(currhost);
	}
	
	return hosts;
}

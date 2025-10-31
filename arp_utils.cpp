/* arp_utils.cpp */

#include "arp_utils.h"
#include "utils.h"


// checks if destMAC is found in arpOut, if so, parses IPv4 address from the string into destIP,
// then returns true. returns false if MAC couldnt be found.
bool checkStatus(std::string destMAC, std::vector<std::string> arpOut, std::string& destIP) {
	for (const std::string &h: arpOut) {
		if (h.find(destMAC) != std::string::npos) {
			try {
				std::pair<std::string, std::string> parsedHost = parseArpOutputLine(h);
				destIP = parsedHost.second;
				return true;
			}
			catch (std::exception &e) {
				throw std::runtime_error(RED + std::string("[arp_utils::checkStatus()] ERROR: ") + e.what());
			}
		}
	}
	destIP = "N/A";
	return false;
}

// parses a single line of arp-scan output and returns a pair <mac, ip>
std::pair<std::string, std::string> parseArpOutputLine(std::string line) {

	std::string mac_addr = line.substr( (line.find('\t') + 1) , (line.substr(line.find('\t') + 1, line.size() - 1).find('\t')));
	std::string ipv4 = line.substr(0, line.find('\t'));
	
	return { mac_addr, ipv4 };
}

// uses arpScanOutput(), parses all ipv4 and MAC address's , returns all in a vector of pairs <mac, ip>.
std::vector<std::pair<std::string, std::string>> parsedArpOutput() {

	std::vector<std::pair<std::string, std::string>> hosts;
	std::vector<std::string> arpout = arpScanOutput();

	for (int i = 0; i < arpout.size(); i++) {
		std::string line = arpout[i];
		
		std::pair host_pair = parseArpOutputLine(line);
		hosts.push_back(host_pair);
	}

	return hosts;
}

// uses popen() to get arp-scan output, and saves each 
// line to a vector EXCEPT for the first two lines (the header) 
// and last three lines (the trailer).
std::vector<std::string> arpScanOutput(){

	FILE* f = popen("arp-scan --localnet", "r");
	if (!f) {
		throw std::runtime_error(RED + std::string("[arp_utils::arpScanOutput()] couldnt create arp-scan pipe!"));
	}
	
	std::vector<std::string> lines;
	char buffer[512];
	int count = 0;
	try {
		while(fgets(buffer, sizeof(buffer), f)) {
			// skip arp-scan header (first two lines)
			if (count >= 2) {
				lines.emplace_back(buffer);
			}
			else { count++; }
		}
		
		// remove arp-scan trailer (last three lines)
		if(lines.size() >= 3) {
			lines.resize(lines.size() - 3);
		}
	}
	catch (std::exception &e) {
		pclose(f);
		throw std::runtime_error(RED + std::string("[arp_utils::arpScanOutput()] arp-scan error: ") + e.what());
	}
	pclose(f);
	return lines;
}

void PrintOut(std::vector<std::pair<std::string, std::string>> parsedout){
	int i = 1;
	std::cout << "\n";
	std::cout << BOLD 
			  << std::left
			  << std::setw(4) << "#"
			  << std::setw(15) << "IPV4"
			  << std::setw(20) << "MAC"
			  << RESET
			  << '\n';

	for (const auto &h : parsedout) {
		std::cout << std::left
				  << std::setw(4) << i << RESET
				  << GREEN
				  << std::setw(15) << h.second
				  << std::setw(20) << h.first << RESET
				  << '\n';
		i++;
	}
}

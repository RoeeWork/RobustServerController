/* arp_utils.cpp */

#include "utils.h"

// gets a line of an arp-scan output, parses the ip and MAC address,returns both in a map<mac, ip>.
std::map<std::string, std::string> parsedArpOutput() {

	std::map<std::string, std::string> hosts;
	std::vector<std::string> arpout = arpScanOutput();

	for (int i = 0; i < arpout.size(); i++) {
		std::string line = arpout[i];
		std::string ipv4 = line.substr(0, line.find('\t'));
		std::string mac_addr = line.substr( (line.find('\t') + 1) , (line.substr(line.find('\t') + 1, line.size() - 1).find('\t')));
		
		hosts[mac_addr] = ipv4;

	}

	return hosts;
}

void PrintOut(std::map<std::string, std::string> parsedout){
	int i = 1;
	for (const auto &p : parsedout) {
		std::cout << "==========Host No." << i << "============\n";
		std::cout << "MAC:\t" << p.first << '\n'
				<< "IPv4:\t" << p.second << '\n';
		i++;
	}
}
// uses popen() to get arp-scan output, and saves each 
// line to a vector EXCEPT for the first two lines (the header) 
// and last three lines (the trailer).
std::vector<std::string> arpScanOutput(){

	FILE* f = popen("arp-scan --localnet", "r");
	if (!f) {
		std::cerr << "pipe failure!\n" << std::endl;
	}
	
	std::vector<std::string> lines;
	char buffer[512];
	int count = 0;
	
	while(fgets(buffer, sizeof(buffer), f)) {
		// skip arp-scan header (first two lines)
		if (count == 2) {
			lines.emplace_back(buffer);
		}
		else { count++; }
	}
	
	// remove arp-scan trailer (last three lines)
	if(lines.size() >= 3) {
		lines.resize(lines.size() - 3);
	}
	return lines;
}

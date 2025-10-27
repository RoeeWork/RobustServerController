/* Commands.cpp */

#include "Commands.h"

int main() {
	std::vector<std::string> arpscan = arpScanOutput();
	std::map<std::string, std::string> parsedout = parsedArpOutput();
	int i = 1;
	for (const auto &p : parsedout) {
		std::cout << "==========Host No." << i << "============\n";
		std::cout << "MAC:\t" << p.first << '\n'
				<< "IPv4:\t" << p.second << '\n';
		i++;
	}
	return 0;
}


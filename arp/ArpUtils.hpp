#include <vector>
#include <iostream>

class ArpUtils {
	public:
		// uses popen() to get arp-scan output, and saves each 
		// line to a vector EXCEPT for the first two lines (the header) 
		// and last three lines (the trailer).
		std::vector<std::string> arpScanOutput();

		// uses arpScanOutput(), parses all ipv4 and MAC address's , returns all in a vector of pairs <mac, ip>.
		std::vector<std::pair<std::string, std::string>> parsedArpOutput();

		// parses a single line of arp-scan output
		std::pair<std::string, std::string> parseArpOutputLine(std::string line);

		// changes MAC address depending on if the corrisponding
		// ipv4 address is found in 'arpOut'.
		// TODO: change to get a Host instead of seperate fields
		bool checkIPv4Status(std::string destIP, std::vector<std::string> arpOut, std::string& destMAC);

		// checks if destMAC is found in arpOut. 
		// if so, parses IPv4 address from the string into destIP,
		// then returns true. returns false if MAC couldnt be found.
		// TODO: change to get a Host instead of seperate fields
		bool checkStatus(std::string destMAC, std::vector<std::string> arpOut, std::string &destIP);
};

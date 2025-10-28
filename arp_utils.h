/* arp_utils.h */
#include "utils.h"

// uses arpScanOutput(), parses all ipv4 and MAC address's , returns all in a vector of pairs <mac, ip>.
std::vector<std::pair<std::string, std::string>> parsedArpOutput();

// parses a single line of arp-scan output
std::pair<std::string, std::string> parseArpOutputLine(std::string line);

// checks if destMAC is found in arpOut, if so, parses IPv4 address from the string into destIP,
// then returns true. returns false if MAC couldnt be found.
bool checkStatus(std::string destMAC, std::vector<std::string> arpOut, std::string &destIP);

// uses popen() to get arp-scan output, and saves each 
// line to a vector EXCEPT for the first two lines (the header) 
// and last three lines (the trailer).
std::vector<std::string> arpScanOutput();

void PrintOut(std::vector<std::pair<std::string, std::string>> parsedout);

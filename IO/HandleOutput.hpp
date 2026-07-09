#include <vector>
#include <iostream>
#include "../host/Host.hpp"

class HandleOutput {
	public:
		// The contents of RSC's help command.
		// WARNING: DO NOT USE TABS, ONLY SPACES!
		static const std::string HELP_TEXT;

		// pretty prints hosts in chosenHosts as a table.
		// TODO: change name.
		static void printHostVectorTable(); 

		static std::vector<Host> StartChooseHostsLoop(std::vector<Host> foundHosts);

		// pretty prints hosts in chosenHosts as a list.
		// only prints ipv4 and mac.
		static void printHostVectorNumberedList(std::vector<Host> hosts); 

		// prints msg if verbose is equal to true. 
		static void verbosePrint(const std::string& msg, bool verbose);
		
};

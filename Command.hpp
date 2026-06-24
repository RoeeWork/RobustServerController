#pragma once
#include "arp_utils.h"
#include "utils.h"

extern bool verbose;

class Command {
	public:
		// Constructor
		Command(bool isFirstRun);
		void removeHost(std::string hostName);
		void changeHostName(std::string currName, std::string newName);
	protected:
		void updateHosts();
	private:
		bool isFirstRun; //what is this for?
		std::vector<host_info> chosenHosts; 
};

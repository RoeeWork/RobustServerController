/* Commands.h */
#include "arp_utils.h"
#include "utils.h"

extern bool verbose;


class Commands {
	public:
		Commands();
		std::vector<host_info> chosenHosts;
		void RemoveHost(std::string hostName);
		void changeHostName(std::string currName, std::string newName);
		bool isFirstRun;
	protected:
		void UpdateHosts();

};

class AddServers: public Commands {
	public:
		AddServers();
		std::vector<host_info> Start();
		void SaveByIPv4();
		void SaveAddrs(std::vector<host_info> addedHosts);
};

class ControlWorker: public Commands {
	public:
		ControlWorker();
		void Start();
	protected:
		std::vector<host_output> hostOutputs;
		void PrintOutput();
};

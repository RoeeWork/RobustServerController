/* Commands.h */
#include "arp_utils.h"
#include "utils.h"

extern bool verbose;


class Commands {
	public:
		std::vector<host_info> chosenHosts;
		void RemoveHost(std::string hostName);
		bool isFirstRun;
	protected:
		Commands();
		void UpdateHosts();

};

class AddServers: public Commands {
	public:
		AddServers();
		std::vector<host_info> Start();
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

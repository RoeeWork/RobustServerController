/* Commands.h */
#include "arp_utils.h"
#include "utils.h"

class Commands {
	public:
		std::vector<host_info> chosenHosts;
	protected:
		Commands();
		void UpdateHosts();

};

class AddServers: public Commands {
	public:
		AddServers();
		std::vector<host_info> Start();

	protected:
		void SaveAddrs();
};

class ControlWorker: public Commands {
	struct host_output {
		std::string name;
		std::string ipv4;
		std::string MAC;
		std::string status; // offline-online
	};
	public:
		void Start();
	protected:
		std::vector<host_output> hostOutputs;
		void PrintOutput();
};

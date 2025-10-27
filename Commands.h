/* Commands.h */

#include "utils.h"

class Commands {
	Commands();
	protected:
		std::vector<host_info> chosenHosts;
		void UpdateHosts();

};

class AddServers: public Commands {
	public:
		std::vector<host_info> Start();

	protected:
		std::vector<host_info> ScanAddresses();
		std::string SaveAddrs();
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

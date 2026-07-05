#include <memory>
#include <string>
#include <vector>
#include "Host.hpp"

class HostList {
	public:
		std::vector<Host> savedHosts;

		// TODO: change name to populateChosenHosts().
		static void updateHosts();

		// TODO: i acutally think this belongs in `HandleCommand`,
		// 		 but ill change it later.
		static void RemoveHost();

		// TODO: i acutally think this belongs in `HandleCommand`,
		// 		 but ill change it later.
		// 		 seperate logic.
		static void changeHostName();
		// search for a specfic host from saved host by his name
		// input: nameToSearch - the name of the host to search for
		// output: either a pointer to the found host or nullptr if not found 
		std::unique_ptr<Host> searchHostByName(std::string nameToSearch);
		// TODO: add Commands contructor.
};

#include <vector>
#include "./Host.hpp"

class HostList {
	public:
		// TODO: change name.
		std::vector<Host> chosenHosts;

		// TODO: change name to populateChosenHosts().
		static void updateHosts();

		// TODO: i acutally think this belongs in `HandleCommand`,
		// 		 but ill change it later.
		static void RemoveHost();

		// TODO: i acutally think this belongs in `HandleCommand`,
		// 		 but ill change it later.
		// 		 seperate logic.
		static void changeHostName();

		// TODO: add Commands contructor.
};

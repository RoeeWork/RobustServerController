#include <vector>
#include "./Host.hpp"
#include "../json/jsonUtils.hpp"

class HostList {
	public:
		// TODO: change name.
		static std::vector<Host> chosenHosts;

		// TODO: change name to populateChosenHosts().
		static void populateChosenHosts();

		// TODO: i acutally think this belongs in `HandleCommand`,
		// 		 but ill change it later.
		static void RemoveHost();

		// TODO: i acutally think this belongs in `HandleCommand`,
		// 		 but ill change it later.
		// 		 seperate logic.
		static void changeHostName();

		// TODO: add Commands contructor.
};

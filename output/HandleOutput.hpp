#include <vector>
#include "../host/Host.hpp"

class HandleOutput {
	public:
		// buffer, handles status (online/offline).
		// TODO: check if this can be replaced by the Host class.
		std::vector<Host> hostOutputs;

		// pretty prints hostOutput.
		// TODO: change name.
		static void printOutput(); 

		// prints msg if verbose is equal to true. 
		static void verbosePrint(const std::string& msg, bool verbose);
		
		// prints the help command to the screen.
		// TODO: Change to a field and create a command
		// 		 called `printHelp()` in `HandleCommand`.
		static void helpCommand();
};

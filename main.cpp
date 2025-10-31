/* main.cpp */
#include "Commands.h"
#include "json_utils.h"


// TODO:
// 	1.	[ ] add TUI
// 	2.	[ ] implement arp-scan
// 	3.	[ ] add help command
// 	4.	[x] add normal cli arugment managment
// 	5.	[x] improve verbosity
// 	6.	[ ] improve security
// 	7.	[ ] add delete server command
// 	8.	[ ] add reset user info command
// 	9.	[ ] add command to add server manually by ipv4
// 	10.	[ ] add command to add server manually by MAC
// 	11.	[ ] add command to change a servers name
// 	12.	[x] add error managment
// 	13. [ ] 
//


void verbose_print(const std::string& msg, bool verbose) {
    if (verbose) std::cout << BLUE << "VERBOSE: " << RESET << msg << std::endl;
}

bool verbose = false;

int main(int argc, char *argv[]) {
	try {
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg == "--verbose" || arg == "-v") {
				verbose = true;
			} else if (arg == "--addservers" || arg == "-a") {
				AddServers add;
				add.Start();
				return 0;

			} else {
				throw std::invalid_argument("Invalid argument");
			}
		}
	}
	catch (std::invalid_argument &e) {
		std::cout << RED <<"[rsc::main()] INVALID ARGUEMENT ERROR: " << RESET << e.what() << std::endl;
		// TODO: print help here
		return 0;
	}
	catch (std::runtime_error &e) {
		std::cout << RED << "[rsc::main()] RUNTIME ERROR: " << RESET << e.what() << std::endl;
		return 0;
	}
	catch(std::exception &e) {
		std::cout << RED << "[rsc::main()] UNKOWN ERROR: " << RESET << e.what() << std::endl;
		return 0;
	}
	ControlWorker cmd;
	cmd.Start();
	return 0;
}



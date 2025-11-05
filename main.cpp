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
// 	7.	[x] add delete server command
// 	8.	[ ] add reset user info command
// 	9.	[ ] add command to add server manually by ipv4
// 	10.	[ ] add command to add server manually by MAC
// 	11.	[ ] add command to change a servers name
// 	12.	[x] add error managment
// 	13. [ ] windows support?
// 	14. [x] fix verbose bug
// 	15. [ ] automation script
//


void verbose_print(const std::string& msg, bool verbose) {
    if (verbose) std::cout << BLUE << "VERBOSE: " << RESET << msg << std::endl;
}

void help_command() {
	std::cout << 
		 R"(USAGE: rsc [OPTIONS] [COMMAND]

Robust Server Controller (rsc)
provides simple functionallity to save server information and automatically find IPv4 addresses.

COMMANDS:
	$ rsc					# lists all saved server information.
	$ rsc --addservers		# adds servers from LAN.
	$ rsc --remove <HOSTNAME>	# removes <HOSTNAME> from the saved servers list.

FLAGS:
	-h,  --help			help for rsc.
	-v,  --verbose 		provides verbose output for rsc.
	-a,  --addservers 	add servers from online servers on LAN.
	-rm, --remove 		remove a saved server profile.

DESCRIPTION:
	rsc is a sever controller written in c++. it provides simple functionallity
	for managing LAN servers whose addresses may change due to a NAT.)" << std::endl;
}

bool verbose = false;

int main(int argc, char *argv[]) {
	try {
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg == "--verbose" || arg == "-v") {
				verbose = true;
			} else if (arg == "--help" || arg == "-h") {
				help_command();
				return 0;
			}
		}
		for (int i = 1; i < argc; ++i) {
			std::string arg = argv[i];
			if (arg == "--addservers" || arg == "-a") {
				AddServers add;
				add.Start();
				return 0;
			} else if (arg == "--remove" || arg == "-rm") {
				AddServers update;
				std::string name = argv[i + 1];
				update.RemoveHost(name);
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



/* main.cpp */
#include "Commands.h"
#include "json_utils.h"


// TODO:
// 	1.	[ ] add TUI
// 	2.	[ ] implement arp-scan
// 	3.	[x] add help command
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
namespace po = boost::program_options; 

int main(int argc, char *argv[]) {
	try {
		po::options_description desc("options");
		desc.add_options()
			("help,h", "produce help messege")
			("verbose,v", "run in verbose mode")
			("addservers,a", "add new servers")
			("remove,rm", po::value<std::string>(), "removes a server");
		
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
		if (vm.count("help")) {
			help_command();
			return 0;
		}
		if (vm.count("verbose")) {
			verbose = true;
		}
		if (!vm.count("addservers") && !vm.count("remove")) {
			ControlWorker cmd;
			cmd.Start();
		} else if(vm.count("addservers") && !vm.count("remove")) {
			AddServers add;
			add.Start();
			return 0;
		} else if(!vm.count("addservers") && vm.count("remove")) {
			AddServers update;
			std::string name = vm["remove"].as<std::string>();
			update.RemoveHost(name);
			return 0;
		} else {
			throw std::invalid_argument("Invalid argument");
		}
	}
	catch (std::invalid_argument &e) {
		std::cout << RED <<"[rsc::main()] INVALID ARGUEMENT ERROR: " << RESET << e.what() << std::endl;
		help_command();
		return 0;
	}
	catch(boost::wrapexcept<boost::program_options::invalid_command_line_syntax> const& e) {
		std::cout << RED <<"[rsc::main()] INVALID ARGUEMENT ERROR: " << RESET << e.what() << std::endl;
		help_command();
		return 0;
	} 
	catch (std::runtime_error &e) {
		std::cout << RED << "[rsc::main()] RUNTIME ERROR: " << RESET << e.what() << std::endl;
		return 0;
	}
	
	catch(po::error const& e) {
		std::cout << RED << "[rsc::main()] CLI ARGUEMENT PARSER ERROR: " << RESET << e.what() << std::endl;
		return 0;
	}
	catch(std::exception &e) {
		std::cout << RED << "[rsc::main()] UNKOWN ERROR: " << RESET << e.what() << std::endl;
		return 0;
	}
	return 0;
}



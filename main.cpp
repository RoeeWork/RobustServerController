/* main.cpp */
#include "Commands.h"
#include "json_utils.h"

void verbose_print(const std::string& msg, bool verbose) { //code rev -> move to utils.h
    if (verbose) std::cout << BLUE << "VERBOSE: " << RESET << msg << std::endl; //code rev -> Add to if bracets
}

// WARNING: DO NOT USE TABS!
// 			using tabs will not align the descriptions correctly.
// 			use spaces instead.
void help_command() {// code rev -> create const str in utils.h and remove this func. print in main the const str.
	std::cout << 
		 R"(USAGE: rsc [OPTIONS] [COMMAND]

Robust Server Controller (rsc)
provides simple functionallity to save server information and automatically find IPv4 addresses.

COMMANDS:
	$ rsc                                               # lists all saved server information.
	$ rsc --addservers                                  # adds servers from LAN.
	$ rsc --addipv4                                     # adds a server by its IPv4 address.
	$ rsc --remove <HOSTNAME>                           # removes <HOSTNAME> from the saved servers list.
	$ rsc --changename <HOSTNAME> --newname <NEWNAME>   # changes <HOSTNAME> to <NEWNAME>.

FLAGS:
	-h,  --help         help for rsc.
	-v,  --verbose      provides verbose output for rsc.
	-a,  --addservers   add servers from online servers on LAN.
	-rm, --remove       remove a saved server profile.
	-cn, --changename   changes a profiles name.

DESCRIPTION:
	rsc is a sever controller written in c++. it provides simple functionallity
	for managing LAN servers whose addresses may change due to a NAT.)" << std::endl;
}

bool verbose = false; //code rev ->  move to utils.h
namespace po = boost::program_options; //code rev ->  move to utils.h

//code rev -> main should be short
//code rev -> split all the main into functions
//code rev -> move all of the logic from the main to a class
int main(int argc, char *argv[]) {
	try {
		AddServers add;
		ControlWorker cmd;
		Commands update;
		po::options_description desc("options");
		desc.add_options()
			("help,h", "produce help messege")
			("verbose,v", "run in verbose mode")
			("addservers,a", "add new servers")
			("changename,cn", po::value<std::string>(), "change a hosts name")
			("newname", po::value<std::string>(), "new host name")
			("addipv4", "add a host by IPv4")
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
		if (vm.count("changename") && vm.count("newname")) {
			std::string name = vm["changename"].as<std::string>();
			std::string newName = vm["NEW-NAME"].as<std::string>();
			update.changeHostName(name, newName);
		} else if (vm.count("changename") && !vm.count("newname")) {
			throw std::invalid_argument("Invalid argument: forgot to input the new name, --newname <name>");

		} else if (!vm.count("changename") && vm.count("newname")) {
			throw std::invalid_argument("Invalid argument: what new name? usage: --changename <old_name> --newname <name>");
		}
		if (vm.count("addipv4")) {
			add.SaveByIPv4();
			return 0;
		}
		if (!vm.count("addservers") && !vm.count("remove")) {
			cmd.Start();
		} else if(vm.count("addservers") && !vm.count("remove")) {
			add.Start();
			return 0;
		} else if(!vm.count("addservers") && vm.count("remove")) {
			std::string name = vm["remove"].as<std::string>();
			update.RemoveHost(name);
			return 0;
		} else {
			throw std::invalid_argument("Invalid argument");
		}
	}
	//code rev -> see which catch needs to move from main
	//code rev -> maybe add our own exceptions class
	//code rev -> in the invalid arguement its reapting code ( catch 1 and catch 2) 
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



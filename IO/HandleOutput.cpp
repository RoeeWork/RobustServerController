#include "./HandleOutput.hpp"

// The contents of RSC's help command.
// WARNING: DO NOT USE TABS, ONLY SPACES!
const std::string HandleOutput::HELP_TEXT =
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
	for managing LAN servers whose addresses may change due to a NAT.)";



// prints the host vector `hosts` in a numbered list.
// only prints IPv4 and MAC addresses.
void HandleOutput::printHostVectorNumberedList(std::vector<Host> hosts) {
int i = 1;
std::cout << "\n";
std::cout << BOLD 
		  << std::left
		  << std::setw(4) << "#"
		  << std::setw(15) << "IPV4"
		  << std::setw(20) << "MAC"
		  << RESET
		  << '\n';

for (const auto &h : hosts) {
	std::cout << std::left
			  << std::setw(4) << i << RESET
			  << GREEN
			  << std::setw(15) << h.getIPv4()
			  << std::setw(20) << h.getMAC()<< RESET
			  << '\n';
	i++;
}
}

std::vector<Host> HandleOutput::StartChooseHostsLoop(std::vector<Host> foundHosts) {
	int hostNum;
	std::vector<Host> chosenAddrs;
	while (true) {
		printHostVectorNumberedList(foundHosts);

		std::cout << "[AddServers::Start()] choose host number (-1 if done): ";
		std::string num;
		std::getline(std::cin, num); 
		try {
			hostNum = stoi(num);
		}
		catch (std::invalid_argument) {
			std::cout << "[AddServers::Start()] please input a valid number.\n" << std::endl;
			continue;
		}
		catch (std::out_of_range) {
			std::cout << "[AddServers::Start()] number out of range.\n" << std::endl;
			continue;
		}

		if (!std::cin) {
			std::cout << "[AddServers::Start()] please input a valid number.\n" << std::endl;
			hostNum = 0;
			continue;
		}
		if (hostNum == -1) {
			if (chosenAddrs.size() == 0) {
				std::cout << "[AddServers::Start()] didnt choose any hosts!\n" << std::endl;
			}
			std::cout << "[AddServers::Start()] stopping...\n" << std::endl;
			break;
		}
		if (hostNum > foundHosts.size() || (hostNum <= 0 && hostNum != -1)) {
			std::cout << "[AddServers::Start()] please input a number that is in range.\n" << std::endl;
			continue;
		}
		
		Host currhost = foundHosts[hostNum - 1];
		std::string hostName;

		std::cout << "[AddServers::Start()] Name your server: ";
		std::getline(std::cin, hostName);

		currhost.setName(hostName);
		chosenAddrs.push_back(currhost);
	}
	return chosenAddrs;
}

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
void HandleOutput::printHostVectorNumberedTable(std::vector<Host> hosts) {
	int hostIndex = 1;
	// TODO: change these to a struct called TableContext? could
	// 		 be useful for printing other tables... and will make
	// 		 it easier to use the printTableHeader() and the
	// 		 printTableHostColumn() methods.
	int rowNumberColumnMargin = 4;
	int IPv4ColumnMargin = 15;
	int MACColumnMargin = 20;

	printNumberedTableHeader(rowNumberColumnMargin, IPv4ColumnMargin, MACColumnMargin);
	for (auto &h : hosts) {
		printNumberedTableHostRow(hostIndex, h, rowNumberColumnMargin, IPv4ColumnMargin, MACColumnMargin);
		hostIndex++;
	}
}

// prints the numbered host table header.
// TODO: seems unintuitive.
void  HandleOutput::printNumberedTableHeader(int rowNumberColumnMargin, int IPv4ColumnMargin, int MACColumnMargin) {
	//
	// #   IPV4           MAC	<---------- prints this!
	// 1   <ipv4_no1>	  <mac_no1>
	// 2   <ipv4_no2>	  <mac_no2>
	// .....
	//
	std::cout << "\n";
	std::cout << BOLD 
			  << std::left
			  << std::setw(rowNumberColumnMargin) << "#"
			  << std::setw(IPv4ColumnMargin) << "IPV4"
			  << std::setw(MACColumnMargin) << "MAC"
			  << RESET
			  << '\n';
}

// prints a new row to the numbered table.
// TODO: seems unintuitive.
void HandleOutput::printNumberedTableHostRow(int rowNumber, Host& h, int  rowNumberColumnMargin, int IPv4ColumnMargin, int MACColumnMargin) {
	//
	// #   IPV4           MAC	
	// 1   <ipv4_no1>	  <mac_no1> <-------- prints this!
	// 2   <ipv4_no2>	  <mac_no2> <-------- prints this!
	// .....
	//
	std::cout << std::left
			  << std::setw(rowNumberColumnMargin) << rowNumber << RESET
			  << GREEN     
			  << std::setw(IPv4ColumnMargin) << h.getIPv4()
			  << std::setw(MACColumnMargin) << h.getMAC()<< RESET
			  << '\n';
}

std::vector<Host> HandleOutput::StartChooseHostsLoop(std::vector<Host> foundHosts) {
	int hostNum;
	std::vector<Host> chosenAddrs;
	while (true) {
		printHostVectorNumberedTable(foundHosts);

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

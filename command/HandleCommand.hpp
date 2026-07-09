#include <iostream>
#include <vector>
#include "../arp/ArpUtils.hpp"
#include "../IO/HandleOutput.hpp"
#include "../host/HostList.hpp"

/* HandleCommand: includes endpoints for each command in `rsc`.
 *				  for example: removeHost is the endpoint
 *				  for `$ rsc --remove`.
 *				  
 *				  WARNING: this class is only ment to be used
 *				  		   in the main function. Do not use this
 *				  		   classes methods inside any other class
 *				  		   other than main.
 */

class HandleCommand {
	public:
		// Prompts user with the hosts that are known on
		// the LAN, and adds the chosen ones into the DB.
		// TODO: seperate logic.
		static void addMultipleHosts();

		// adds a single host using an IPv4 address.
		static void addByIPv4(std::string ipv4);

		// adds a single host using an MAC address.
		static void addByMAC(std::string mac);

		// removes a single host using it's name.
		static void removeHost(std::string hostName);

		// chages a host name from oldName into newName.
		static void changeHostName(std::string oldName, std::string newName);

		// displays saved hosts with an updated `status` field.
		// TODO: change name.
		static void printHosts();

		// prints the help command to the screen.
		static void printHelp();

		// resets rsc into default settings.
		static void factoryReset();
};

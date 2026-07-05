#include "HostList.hpp"

std::unique_ptr<Host> HostList::searchHostByName(std::string nameToSearch) {
	// go over all the host and search for a match
	for (Host host : this->savedHosts) {
		if (host.getName() == nameToSearch) {
			return std::make_unique<Host>(host);
		}
	}
	return std::unique_ptr<Host>(nullptr); // if nothing has been found return null pointer
}

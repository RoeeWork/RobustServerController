#include "HostList.hpp"


void HostList::populateChosenHosts() {
	verbose_print("[Commands::UpdateHosts()] starting Commands::UpdateHosts().", verbose);
	try {
		json j_hosts_data = JsonUtils::getJsonArrayFromFile();
		std::vector<Host> hosts = JsonUtils::deserializeJsonArray(j_hosts_data);

		chosenHosts.clear();
			for (auto &host : hosts) {
			chosenHosts.push_back(host);
		}
	}
	catch (const std::exception &e) {
		verbose_print("[Commands::UpdateHosts()] found exception", verbose);
		throw std::runtime_error(std::string("[Commands::UpdateHosts()] FILE ERROR: ") + e.what());
	}
}

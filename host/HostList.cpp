#include "HostList.hpp"


// populates `chosenHosts` with hosts saved on the json DB.
void HostList::populateChosenHosts() {
	try {
		json j_hosts_data = JsonUtils::getJsonArrayFromFile(JsonUtils::JSON_FILE_PATH);
		std::vector<Host> hosts = JsonUtils::deserializeJsonArray(j_hosts_data);

		chosenHosts.clear();
			for (auto &host : hosts) {
			chosenHosts.push_back(host);
		}
	}
	catch (const std::exception &e) {
		throw std::runtime_error(std::string("[Commands::UpdateHosts()] FILE ERROR: ") + e.what());
	}
}

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

std::ostream& operator<<(std::ostream& os, const HostList& hosts) {
	int hostIndex = 1;	

	int rowNumberColumnMargin = 4;
	int nameColumnMargin = 20;
	int IPv4ColumnMargin = 15;
	int MACColumnMargin = 20;
	int statusColumnMargin = 15;

	// header
	os << "\n";
	os << BOLD 
		<< std::left
		<< std::setw(rowNumberColumnMargin) << "#"
		<< std::setw(nameColumnMargin) << "NAME"
		<< std::setw(IPv4ColumnMargin) << "IPV4"
		<< std::setw(MACColumnMargin) << "MAC"
		<< std::setw(statusColumnMargin) << "STATUS"
		<< RESET
		<< '\n';

	for (const auto &h : hosts.getChosenHosts()) {
		os << std::setw(rowNumberColumnMargin) << hostIndex
			<< h << '\n';
		hostIndex++;
	}
	return os;
}

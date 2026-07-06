// TODO: add verbosity.
#include "jsonUtils.hpp"

/// @brief Serializes host information to JSON format
/// @param jsonResult storage for the resulting JSON object
/// @param infoToConvert the host information to convert
void JsonUtils::serialize(json& jsonResult, const Host& host) {
	jsonResult["Name"] = host.getName();
	jsonResult["IPv4"] = host.getIPv4();
	jsonResult["MAC_Address"] = host.getMAC();
}

/// @brief Deserializes JSON data to host information
/// @param jsonToConvert the JSON object containing host information
/// @param infoResult storage for the resulting host information
void JsonUtils::deserialize(const json& jsonToConvert, Host& infoResult) {
	validateJsonField(jsonToConvert, "Name");
	validateJsonField(jsonToConvert, "MAC_Address");
	validateJsonField(jsonToConvert, "IPv4");

	infoResult.setName(jsonToConvert["Name"]);
	infoResult.setIPv4Address(jsonToConvert["IPv4"]);
	infoResult.setMACAddress(jsonToConvert["MAC_Address"]);
}

// deserializes an entire json array into a Host vector.
std::vector<Host> JsonUtils::deserializeJsonArray(json j_host_data) {
	std::vector<Host> hosts;
	for (auto &j : j_host_data) {
		deserialize(j, hosts.emplace_back());
	}
	return hosts;
}

/// @brief Validates the presence and type of a required field in a JSON object
/// @param jsonToConvert the JSON object to validate
/// @param fieldName the name of the field to validate
void JsonUtils::validateJsonField(const json& jsonToConvert, const std::string& fieldName) {
	if (!jsonToConvert.contains(fieldName)) {
		throw std::invalid_argument("[JsonUtils::validateJsonField] Missing required field: " + fieldName); // need to catch this exception in the caller function of deserialize and handle it properly
	}
	if (!(jsonToConvert[fieldName].is_string())) {
		throw std::invalid_argument("[JsonUtils::validateJsonField] Field '" + fieldName + "' has an incorrect type."); // same as above
	}
}


// creates json file in `file`.
// TODO: add method to ensure json file path integrity.
void JsonUtils::createJsonFile(std::filesystem::path file) {
	std::ofstream j_file(file);
	j_file << "[]";
	j_file.close();
}

// validates if `file` exists in the filesystem.
void JsonUtils::validateJsonFileExistence(std::filesystem::path file) {
	if (!std::filesystem::exists(file)) {
		throw std::runtime_error("[JsonUtils::validateJsonFileExistence] no serverinfo.json...");
	}
}

// returns true if `file` exists in the filesystem,
// false otherwise.
bool JsonUtils::jsonFileExists(std::filesystem::path file){
	if (!std::filesystem::exists(file)) {
		return false;
	}
	return true;
}

// parses a json file to a json array.
void JsonUtils::parseFileToJsonArray(json& j_hosts_data, std::filesystem::path file) {
	std::ifstream infile(file);
	if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
			infile >> j_hosts_data;
			if ( !j_hosts_data.is_array()) {
				j_hosts_data = json::array();
			}
	}
	infile.close();
}

// returns a json array which contains the contents of `file`
json JsonUtils::getJsonArrayFromFile(std::filesystem::path file) {
			if (!jsonFileExists(file)) {
				createJsonFile(file);
			}

			json j_hosts_data = json::array();

			try {
				parseFileToJsonArray(j_hosts_data, file);
			}
			catch (json::parse_error &e) {
					std::cerr << "[AddServers::SaveAddrs()] ERROR: parse error. Resetting.";
					j_hosts_data = json::array();
			}
			return j_hosts_data;
}

// writes a json array `arr` into file `file`.
void JsonUtils::writeArrayToFile(json arr, std::filesystem::path file) {
	std::ofstream outfile(file);
	outfile << arr.dump(4);
	outfile.close();
}

// appends and saves `addedHosts` into `file`
void JsonUtils::saveHostsToFile(std::vector<Host> addedHosts, std::filesystem::path file) {
	try {
		if (addedHosts.size() != 0) {
			json j_hosts_data = getJsonArrayFromFile(file);

			for (auto &h : addedHosts) {
				serialize(j_hosts_data.emplace_back(), h);
			}

			writeArrayToFile(j_hosts_data, file);
		}
	}

	catch (std::exception &e) {
		throw std::runtime_error(RED + std::string("[AddServers::SaveAddrs()] ERROR: ") + e.what());
	}
}


// TODO: will be smarter to make the method change a certain field instead of
// 		 exculsivly the host_name...
// 		 MOVE TO HOST_LIST
void JsonUtils::changeHostName(std::string currName, std::string newName) {
	json j_hosts_data = json::array();

	validateJsonFileExistence();
	parseFileToJsonArray(j_hosts_data);

	// Q?: get into a serprate method called findField
	for (auto it = j_hosts_data.begin(); it != j_hosts_data.end(); ++it) {
		if (it->contains("Name") && (*it)["Name"] == currName) {
			(*it)["Name"] = newName;
			break;
		}
	}

	std::ofstream(JSON_FILE_PATH,  std::ios::trunc) << j_hosts_data.dump(4);
}

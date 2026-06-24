// TODO: add verbosity.
#include "jsonUtils.hpp"

void JsonUtils::serialize(json& jsonResult, const Host& host) {
	jsonResult["Name"] = host.getName();
	jsonResult["IPv4"] = host.getIPv4();
	jsonResult["MAC_Address"] = host.getMAC();
}

void JsonUtils::deserialize(const json& jsonToConvert, Host& infoResult) {
	validateJsonField(jsonToConvert, "Name");
	validateJsonField(jsonToConvert, "MAC_Address");
	validateJsonField(jsonToConvert, "IPv4");

	infoResult.setName(jsonToConvert["Name"]);
	infoResult.setIPv4Address(jsonToConvert["IPv4"]);
	infoResult.setMACAddress(jsonToConvert["MAC_Address"]);
}

void JsonUtils::validateJsonField(const json& jsonToConvert, const std::string& fieldName) {
	if (!jsonToConvert.contains(fieldName)) {
		throw std::invalid_argument("Missing required field: " + fieldName); // need to catch this exception in the caller function of deserialize and handle it properly
	}
	if (!(jsonToConvert[fieldName].is_string())) {
		throw std::invalid_argument("Field '" + fieldName + "' has an incorrect type."); // same as above
	}
}
// creates a json file in JSON_FILE_PATH.
// TODO: Will be smarter to add a string parameter like "filename" and create according to that...
void JsonUtils::createJsonFile() {
		if (!std::filesystem::exists(JSON_FILE_PATH)) {
			std::ofstream file(JSON_FILE_PATH);
			file << "[]";
			file.close();
		}
}

// Validates if JSON_FILE_PATH exists.
// TODO: Will be smarter to add a string parameter like "filename" and validate according to that...
void JsonUtils::validateJsonFileExistence() {
	if (!std::filesystem::exists(JSON_FILE_PATH)) {
		throw std::runtime_error("no serverinfo.json...");
	}
}

// Parses a json file to a json array j_hosts_data.
void JsonUtils::parseFileToJsonArray(json& j_hosts_data) {
	try {
		std::ifstream infile(JSON_FILE_PATH);
		if (infile.good() && infile.peek() != std::ifstream::traits_type::eof()) {
				infile >> j_hosts_data;
				if ( !j_hosts_data.is_array()) {
					j_hosts_data = json::array();
				}
		}
		infile.close();
	}
	catch (json::parse_error &e) {
			throw std::runtime_error(RED + std::string("[Commands::RemoveHosts()] JSON ERROR: Failed to parse serverinfo.json:") + e.what());
	}
}

void JsonUtils::changeHostName(std::string currName, std::string newName) {
	try {
		json j_hosts_data = json::array();

		validateJsonFileExistence();
		parseFileToJsonArray(j_hosts_data);

		for (auto it = j_hosts_data.begin(); it != j_hosts_data.end(); ++it) {
			if (it->contains("Name") && (*it)["Name"] == currName) {
				(*it)["Name"] = newName;
				break;
			}
		}

		std::ofstream(root / "serverinfo.json", std::ios::trunc) << j_hosts_data.dump(4);
	}

	catch (const std::exception &e) {
    	throw std::runtime_error(std::string("[Commands::RemoveHost()] FILE ERROR: ") + e.what());
	}
}

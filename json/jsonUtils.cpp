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

void validateJsonField(const json& jsonToConvert, const std::string& fieldName) {
	if (!jsonToConvert.contains(fieldName)) {
		throw std::invalid_argument("Missing required field: " + fieldName); // need to catch this exception in the caller function of deserialize and handle it properly
	}
	if (!(jsonToConvert[fieldName].is_string())) {
		throw std::invalid_argument("Field '" + fieldName + "' has an incorrect type."); // same as above
	}
}

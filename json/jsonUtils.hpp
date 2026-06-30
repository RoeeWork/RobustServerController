#pragma once
#include "../host/Host.hpp"
#include "../utils.h"

using nlohmann::json;

// TODO: 1. Add comments
//   	 2. Add Try/Catch blocks
//   	 3. 

class JsonUtils {
    public:
        /// @brief Serializes host information to JSON format
        /// @param jsonResult storage for the resulting JSON object
        /// @param infoToConvert the host information to convert
        void static serialize(json& jsonResult, const Host& host);
        /// @brief Deserializes JSON data to host information
        /// @param jsonToConvert the JSON object containing host information
        /// @param infoResult storage for the resulting host information
        void static deserialize(const json& jsonToConvert, Host& infoResult);

        void static validateJsonFileExistence();
		void static parseFileToJsonArray(json& j_hosts_data);
		void static changeHostName(std::string currName, std::string newName);
		void static createJsonFile();

private:
    /// @brief Validates the presence and type of a required field in a JSON object
    /// @param jsonToConvert the JSON object to validate
    /// @param fieldName the name of the field to validate
    void static validateJsonField(const json& jsonToConvert, const std::string& fieldName);
    const static inline std::filesystem::path JSON_FILE_PATH = root / "serverinfo.json"; // name of the JSON file to store hosts information
};

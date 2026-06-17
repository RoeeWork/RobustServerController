#pragma once
#include "../host/Host.hpp"

using nlohmann::json;

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

private:
    /// @brief Validates the presence and type of a required field in a JSON object
    /// @param jsonToConvert the JSON object to validate
    /// @param fieldName the name of the field to validate
    void static validateJsonField(const json& jsonToConvert, const std::string& fieldName);
};

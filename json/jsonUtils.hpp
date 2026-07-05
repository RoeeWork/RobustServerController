#include "../host/Host.hpp"

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

		// adds `addedHosts` to `chosenHosts and saves to `serverinfo.json`.
		// TODO: seperate logic.
		void static saveAddrs(std::vector<Host> addedHosts);

		// validates if JSON_FILE_PATH exists.
        void static validateJsonFileExistence();

		// parses a json file to a json array.
		void static parseFileToJsonArray(json& j_hosts_data);
		static bool JsonFileExists();

		// creates json file in `JSON_FILE_PATH`.
		static void createJsonFile();

		static std::vector<Host> deserializeJsonArray(json j_host_data);
		static json getJsonArrayFromFile();
		static void writeArrayToFile(json arr);
		static void saveHostsToFile(std::vector<Host> addedHosts);
	private:
		/// @brief Validates the presence and type of a required field in a JSON object
		/// @param jsonToConvert the JSON object to validate
		/// @param fieldName the name of the field to validate
		void static validateJsonField(const json& jsonToConvert, const std::string& fieldName);

		const static inline std::filesystem::path JSON_FILE_PATH = root / "serverinfo.json"; // name of the JSON file to store hosts information
};

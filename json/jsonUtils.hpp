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
        static void serialize(json& jsonResult, const Host& host);

        /// @brief Deserializes JSON data to host information
        /// @param jsonToConvert the JSON object containing host information
        /// @param infoResult storage for the resulting host information
        static void deserialize(const json& jsonToConvert, Host& infoResult);

		// appends and saves `addedHosts` into `file`
		static void saveHostsToFile(std::vector<Host> addedHosts, std::filesystem::path file);

		// parses a json file to a json array.
		static void parseFileToJsonArray(json& j_hosts_data, std::filesystem::path file);

		// creates json file in `file`.
		// TODO: add method to ensure json file path integrity.
		static void createJsonFile(std::filesystem::path file);
		
		// writes a json array `arr` into file `file`.
		static void writeArrayToFile(json arr, std::filesystem::path file);

		// validates if `file` exists in the filesystem.
        static void validateJsonFileExistence(std::filesystem::path file);

		// returns true if `file` exists in the filesystem,
		// false otherwise.
		static bool jsonFileExists(std::filesystem::path file);

		// deserializes an entire json array into a Host vector.
		static std::vector<Host> deserializeJsonArray(json j_host_data);
		
		// returns a json array which contains the contents of `file`
		static json getJsonArrayFromFile(std::filesystem::path file);
		
		const static inline std::filesystem::path JSON_FILE_PATH = root / "serverinfo.json"; // name of the JSON file to store hosts information
	private:
		/// @brief Validates the presence and type of a required field in a JSON object
		/// @param jsonToConvert the JSON object to validate
		/// @param fieldName the name of the field to validate
		void static validateJsonField(const json& jsonToConvert, const std::string& fieldName);

};

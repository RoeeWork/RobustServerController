#include "utils.h"

using nlohmann::json;

// converts host_info to json format
void to_json(json& j, const host_info& host);
void from_json(const json& j, host_info& host);

#include "utils.h"

using nlohmann::json;

// converts host_info to json format
void to_json(json& j, const host_info& host);
void from_json(json& j, const host_info& host);

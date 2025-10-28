#include "json_utils.h"

void to_json(json& j, const host_info& host) {
	j = json {
		{"Name", host.name},
		{"MAC_Address", host.MAC},
		{"IPv4", host.IPv4},
	};
}
